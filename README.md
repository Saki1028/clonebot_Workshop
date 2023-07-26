A slight modification from Dr. Rei Lee's [Conebot](https://github.com/rei039474/ConeBot)

Dependency:
1. Arduino
2. Dr. Rei Lee's [package](https://github.com/rei039474/Dynamixel_XL330_Servo_Library) to control dynamixel motors (XL330 series)

Steps:
1. Download and install Dynamixel Wizard

2. Connect computer to motors. Laptop USB--> U2D2 microUSB-->right side of motor 1--> left side of motor 1--> right side of motor 2--> left side of the motor --> battery. Check the pinout of the U2D2 and dynamixels to make sure you are connecting them properly (VDD, GND, and Data, should connect to one another) 

3. In the Dynamixel Wizard, scan the USB port for Baudrate 57600 to find the motors. After the motor is found, make sure torque is off, then change settings for both:
- Baudrate to 115200 bps
- ID 1 and 2 respectively
- Control mode to PWM (not velocity or position).
- Turn torque on and toggle the diagram to get it moving! You only have to do this once.

5. Install the ESP32 library (from espressif) in the Arduino IDE

6. Using the board and a microUSB, connect to ESP32 cam, flash and run a bit of sample code (try CameraWebServer). https://randomnerdtutorials.com/esp32-cam-video-streaming-face-recognition-arduino-ide/

8. Download the Conebot code and open it in Arduno IDE

9. In `wifi_info.h', set it to "WiFi Option 2: Set up your own Wi-Fi network access point with SSID and password" by commenting out the first option.

10. Upload the code onto the board, connect to its network (SSID and password are in "wifi_info.h"), and visit the IP address that it spits out in the Serial monitor. It should show you live video feed, as well as a button display! Try turning the LED on and off.
  
11. Set up the breadboard: hook up servo, ESP32 cam, battery, and motors. (Schematic included)

12. Again, connect to the ESP32's network, and go to the same IP address. You should be able to see the video stream and control all of the motors!

13. Prototype and build a superstructure

14. Done!
