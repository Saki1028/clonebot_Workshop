A slight modification from Dr. Rei Lee's [Conebot](https://github.com/rei039474/ConeBot)

# Parts（必要部品）:
* Computation: esp32-cam
* Motor Programmer: ROBOTIS U2D2 part
* Motors: DYNAMIXEL XL330-M077-T motor
* Wheels: omni wheels
* Breadboards: mini breadboard sets
* Power: power bank Anker 321
* Cable: usbc-to-c cable
* caster balls


# Dependency（準備）:
1. [Arduino IDE](https://www.arduino.cc/en/software)
2. Dr. Rei Lee's [package](https://github.com/rei039474/Dynamixel_XL330_Servo_Library) to control dynamixel motors (XL330 series)
Download by click code--> download ZIP
unzip ait and move the directoriy to `~/Documents/Arduino/libraries/`

3. [Dynamixel Wizard](https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_wizard2/)
4. Please refer to the following repo for the XL330 Servo library under Arduino IDE:  
[rei039474/Dynamixel_XL330_Servo_Library](https://github.com/rei039474/Dynamixel_XL330_Servo_Library)


# Steps:
## Part A: Dynamixel and motor setup
1. Download and install [Dynamixel Wizard](https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_wizard2/)  
   [Dynamixel Wizard](https://emanual.robotis.com/docs/en/software/dynamixel/dynamixel_wizard2/)をインストールする  

3. Connect computer to motors.  
   PCとモータを接続する。  
   > Laptop USB--> U2D2 microUSB-->right side of motor 1--> left side of motor 1--> right side of motor 2--> left side of the motor --> battery.
   Check the pinout of the U2D2 and dynamixels to make sure you are connecting them properly (VDD, GND, and Data, should connect to one another)
   U2D2とDynamixelの入力・出力を正しく接続すること
   

5. In the Dynamixel Wizard, scan the USB port for Baudrate 57600 to find the motors. After the motor is found, make sure torque is off, then change settings for both:  
   Dynamixel Wizardを起動する。そのソフトウェアでモーターのIDとボードレートをスキャンする。
- Baudrate to 115200 bps（ボードレートを正しい値（おおよそ115200bps）に設定）
- ID 1 and 2 respectively
- Control mode to PWM (not velocity or position).
- Turn torque on and toggle the diagram to get it moving! You only have to do this once.

## Part B: ESP32 Board and webcam setup
1. Download and install [Arduino IDE](https://www.arduino.cc/en/software)  
   [Arduino IDE](https://www.arduino.cc/en/software)をインストールし起動する

2. Install the ESP32 Board (from espressif) in the Arduino IDE:
   下記を参考に、ESP32 Board (from espressif)をインストールする

   > 1. Tools--> Board --> Boards Manager... (左の順にオプションを選択し、Boards Managerウィンドウを開く)![BoardsManager](images/BoardsManager.png)
   > 2. Type esp32 and select esp32 by Expressif　（「esp32」で検索し、「esp32 by Expressif」を選択する）![ESP32byEspressif](images/ESP32byEspressif.png)
   > 3. Install

   This may take a moment（インストールに時間がかかる可能性があります）
![img1](images/ArduinoIDE1.png)


3. Using the board and a microUSB, connect to ESP32 cam, flash and run a bit of sample code (try [CameraWebServer](https://randomnerdtutorials.com/esp32-cam-video-streaming-face-recognition-arduino-ide/)).
   基板とUSBを用いて、ESP32カメラをPCに接続する。その後、下記に示す要領でカメラWebサーバの起動を行う。

select the board by going to:
> tools-->boards> ESP32 Arduino --> select AI Thinker ESP32-CAM
then select the port:
> tools--> port--> there should be something like /dev/usb***** on mac or COM*** on Windows.
then go to:
> File-->Examples-->ESP32-->Camera-->CameraWebServer
put in your wifi credentials
```
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";
```
Uncomment this line `#define CAMERA_MODEL_AI_THINKER ` 
and comment out `//#define CAMERA_MODEL_ESP_EYE `

hit the green arrow button on the left to upload the code to the microcontroller

if you go to tools--> serial monitor it will print out an IP address you can go to in a browser from a computer on the same network.


![img2](images/ArduinoIDE2.png)

6. Download this repo and open the folder Conebot_Control in the Arduno IDE
   ESP32Servoライブラリをダウンロードする
   あらかじめローカルにダウンロードしておいたDynamixel XL330 Arduino Library.ZIPを取り込む

> File-->Open-->Conebot-main-->Conebot_Control-->Conebot_Control.ino

You will also need the ESP32Servo library
> Sketch-->Include Library-->Library Manager-->Type ESP32Servo and install it.

And the Dynamixel XL330 Arduino Library
> Sketch-->Include Library--> Add .ZIP Library and select Dynamixel XL330 Arduino Library.ZIP that we downloaded earlier


![img3](images/ArduinoIDE4.png)

7. In `wifi_info.h', set it to "WiFi Option 2: Set up your own Wi-Fi network access point with SSID and password" by commenting out the first option.
   Wifi設定で、自分で設定したデバイスの名前とパスワードを選択し、接続する。

9. Upload the code onto the board, connect to its network (SSID and password are in "wifi_info.h"), and visit the IP address that it spits out in the Serial monitor. It should show you live video feed, as well as a button display! Try turning the LED on and off.
    

## Part C: ESP32 Board and webcam setup
9. Set up the breadboard: hook up servo, ESP32 cam, battery, and motors. (Schematic included)

10. Again, connect to the ESP32's network, and go to the same IP address. You should be able to see the video stream and control all of the motors!

    
![img4](images/Controler.png)
![img5](images/Controler2.png)
![img6](images/ESP32-CAM.png)

12. Build your robots!
    Brainstorm your ideas for your robots. Prototype and build a superstructure
    これでロボットの基礎は完成です。どのような機能をつけるか等自由にアイデアを出していただき、プロトタイプを作成してください。

14. Done!
