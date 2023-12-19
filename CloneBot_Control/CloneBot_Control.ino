#include "esp_camera.h"
#include <WiFi.h>
#include "esp_timer.h"
#include "img_converters.h"
#include "Arduino.h"
#include "fb_gfx.h"
#include "soc/soc.h"             // disable brownout problems
#include "soc/rtc_cntl_reg.h"    // disable brownout problems
#include "esp_http_server.h"
#include <ESP32Servo.h>
// #include <SoftwareSerial.h>
#include "wifi_info.h"

#include "esp_system.h" //This inclusion configures the peripherals in the ESP system.
#include "esp_himem.h"
#include "esp32-hal-psram.h"
extern "C"
{
  #include <esp_spiram.h>
}


#define ledPin      4
#define liftyPin    15
#define SERVO_STEP  5

#define CAMERA_MODEL_AI_THINKER // Has PSRAM
#include "webcam_pins.h"
#include "camera_index.h"

// Setting up servo motors with 2 dummy onesin the beginning
Servo servoN1; //dummy
Servo servoN2; //dummy
Servo lifty;


// Setting up Dynamixel and Name your robot!
#include <HardwareSerial.h>
#include "XL330.h"
XL330 robot;
// Set the SoftwareSerial RX & TX pins
HardwareSerial mySerial(1);
// SoftwareSerial mySerial(14, 13); 
// Set the default Dynamixel servoID to talk to
int servoID = 1;
int servoID2 = 2;
int servo1Speed = 0;
int servo2Speed = 0;

// Main control variables
byte cmmd = 'c';
byte preCmmd;
byte lift;
int count;

void setup() {
  psramInit();
  esp_spiram_init();
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
  
  lifty.setPeriodHertz(50);    // standard 50 hz servo
  // servoN1.attach(2, 1000, 2000); //dummy setup
  // servoN2.attach(16, 1000, 2000); //dummy setup
  lifty.attach(liftyPin, 540, 2300);
  lifty.write(0);
  
  Serial.begin(115200);
  Serial.setDebugOutput(false);

  // Camera init
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_SVGA;
  config.pixel_format = PIXFORMAT_JPEG; // for streaming
  //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;
  
  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if(config.pixel_format == PIXFORMAT_JPEG){
    if(psramFound()){
      config.jpeg_quality = 10;
      config.fb_count = 2;
      config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
      // Limit the frame size when PSRAM is not available
      config.frame_size = FRAMESIZE_SVGA;
      config.fb_location = CAMERA_FB_IN_DRAM;
    }
  } else {
    // Best option for face detection/recognition
    config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
    config.fb_count = 2;
#endif
  }
  
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  
 //// WiFi Option 1: Setting up Wi-Fi connection to existed network
//  WiFi.begin(ssid, NULL);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.print("Camera Stream Ready! Go to: http://");
//  Serial.println(WiFi.localIP());
  
  // WiFi Option 2: Set up your own Wi-Fi network access point with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  //// Start streaming web server
  startCameraServer();
  // // Blink LED once the server is up
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 10);
  delay(300);
  analogWrite(ledPin, 0);
  
  //// Setup and initiate Software Serial for robot
  mySerial.begin(115200, SERIAL_8N1, 14, 13);
  // mySerial.begin(115200);
  robot.begin(mySerial); // Hand in the serial object you're using
  // Set motor speed to 0
  robot.setJointSpeed(servoID, 0);
  robot.setJointSpeed(servoID2, 0);

  robot.sendPacket_1byte(servoID, 64, 0);
  delay(50);
  robot.sendPacket_1byte(servoID2, 64, 0);
  delay(50);

  robot.setControlMode(servoID, 16);
  delay(50);
  robot.setControlMode(servoID2, 16);
  delay(50);

  robot.sendPacket_1byte(servoID, 64, 1);
  delay(50);
  robot.sendPacket_1byte(servoID2, 64, 1);
  delay(50);
}

void loop() {
  //  robot.setJointSpeed(servoID, -500);
  //  delay(500);
  //  robot.setJointSpeed(servoID, 0);
  // delay(60);
  // robot.setJointSpeed(servoID2, -500);
  // delay(500);
  // robot.setJointSpeed(servoID2, 0);
   
  command(cmmd, lift);
   delay(50);


  // Emergency Stop: losing wifi connection or no update for too long
  if (WiFi.softAPgetStationNum() < 1){
    cmmd = 'c';
    lift = 'b';
    count = 0;
    }
}