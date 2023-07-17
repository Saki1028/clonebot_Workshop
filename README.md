A slight modification from Dr. Rei Lee's [Conebot](https://github.com/rei039474/ConeBot)

Dependency:
1. Arduino
2. Dr. Rei Lee's [package](https://github.com/rei039474/Dynamixel_XL330_Servo_Library) to control dynamixel motors (XL330 series)

Pre-req:
1. program two dynamixel XL330 motors
- have ID 1 and 2
- baudrate 115200
- in PWM control mode (not velocity or position)

Wifi information is in `wifi_info.h`
Main file is `ConeBot_Control.ino`. Put the board in AP mode to host its own WiFi. 
