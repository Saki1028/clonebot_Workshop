void command(byte cmd, byte lift){
  switch (lift) {
    case 97: //'a'lift
      //Serial.println ("lift");
      //analogWrite(ledPin, 50);
      //digitalWrite(ledPin, HIGH);
      lifty.write(90);
      break;
      
    case 98://'b'down
      //Serial.println ("down");
      //digitalWrite(ledPin, LOW);
      lifty.write(0);
      break;
      
    case 99://'c'light
      //Serial.println ("lift");
      analogWrite(ledPin, 30);
      //digitalWrite(ledPin, LOW);
      //myservo.write(20);
      break;
      
    case 100://'d'no_light
      //Serial.println ("lift");
      analogWrite(ledPin, 0);
      //digitalWrite(ledPin, LOW);
      //myservo.write(20);
      break;
    } //Switch
  
  switch (cmd) {
    case 106://'j'joystick control
      robot.setJointSpeed(servoID, (servo1Speed-1000));
      delay(10);
      robot.setJointSpeed(servoID2, (servo2Speed-1000));
      delay(50);
      //Serial.println((servo1Speed-1000));
      break;  
      
    case 97: //'a'front
      robot.setJointSpeed(servoID, 304);
      delay(100);
      robot.setJointSpeed(servoID, 0);
      delay(60);
      robot.setJointSpeed(servoID2, -304);
      delay(100);
      robot.setJointSpeed(servoID2, 0);
      //Serial.println ("a");
      delay(60);
      break;  

    case 98://'b'back
      robot.setJointSpeed(servoID, -300);
      delay(100);
      robot.setJointSpeed(servoID, 0);
      delay(50);
      robot.setJointSpeed(servoID2, 300);
      delay(100);
      robot.setJointSpeed(servoID2, 0);
      //Serial.println ("b");
      delay(50);
      break;

    case 99://'c'stop
      robot.setJointSpeed(servoID, 0);
      delay(10);
      robot.setJointSpeed(servoID2, 0);
      //delay(50);
      //Serial.println ("c");
      break;
      
    case 100://'d'right
      robot.setJointSpeed(servoID, 200);
      delay(10);
      robot.setJointSpeed(servoID2, 200);
      //Serial.println ("d");
      break;
      
    case 101://'e'left
      robot.setJointSpeed(servoID, -200);
      delay(10);
      robot.setJointSpeed(servoID2, -200);
      //Serial.println ("e");
      break;

    case 102: //'f' fast front
      robot.setJointSpeed(servoID, 300);
      delay(10);
      robot.setJointSpeed(servoID2, -300);
      //Serial.println ("a");
      break;  

    case 103://'g' fast back
      robot.setJointSpeed(servoID, -300);
      delay(10);
      robot.setJointSpeed(servoID2, 300);
      //Serial.println ("b");
      break;

    case 116://'t' test dance
      lifty.write(90);
      delay(1000);
      
      for(int i = 0; i < 10; i++){
        robot.setJointSpeed(servoID, 304);
        delay(100);
        robot.setJointSpeed(servoID, 0);
        delay(60);
        robot.setJointSpeed(servoID2, 855);
        delay(100);
        robot.setJointSpeed(servoID2, 0);
      //Serial.println ("a");
        delay(60);
        }
      
      robot.setJointSpeed(servoID, 400);
      delay(10);
      robot.setJointSpeed(servoID2, 855);
      delay(1500);
      
      robot.setJointSpeed(servoID, 0);
      delay(10);
      robot.setJointSpeed(servoID2, 0);
      delay(200);
      
      lifty.write(0);
      delay(1800);
      
      for(int j = 0; j < 10; j++){
        robot.setJointSpeed(servoID, 855);
        delay(100);
        robot.setJointSpeed(servoID, 0);
        delay(60);
        robot.setJointSpeed(servoID2, 300);
        delay(100);
        robot.setJointSpeed(servoID2, 0);
        //Serial.println ("b");
        delay(60);
        }
        
      robot.setJointSpeed(servoID, 855);
      delay(10);
      robot.setJointSpeed(servoID2, 500);
      delay(1500);
      
      robot.setJointSpeed(servoID, 0);
      delay(10);
      robot.setJointSpeed(servoID2, 0);
      delay(1000);

      lifty.write(90);
      delay(100);
      lifty.write(0);
      delay(100);
      lifty.write(90);
      delay(100);
      lifty.write(0);
      delay(100);
      cmmd = 'c';
      //Serial.println ("b");
      break;
    } //Switch
  }