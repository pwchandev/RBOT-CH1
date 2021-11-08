/*
 This sketch is the proportional control routine of DOF4 robot arm.
 It uses the potentiometers (variable resistors) to input the control settings
 1. open and close claw (claw)
 2. extend and contract robot arm (turn left and right left-servo)
 3. lift up and down robot arm (turn left and right right-servo)
 4. turn left and right robot arm (bottom)

 Circuit:
 * Arduino Robot arm

 created 9 August 2021
 by Peter Chan
*/

#include <Servo.h>
// twelve servo objects can be created on most boards
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
Servo servo3;  // create servo object to control a servo
Servo servo4;  // create servo object to control a servo

int servoValue[4] = {0,0,0,0};
float readValue = 0.0;
float sumValue = 0.0;
float servoRead = 0.0;
float offset = 100.0;
int servoMin = 10;
int servoMax = 160;

int servoPin[4] = {3,6,9,10};     // servo PWM pins [claw, left(extend), right(up), bottom(turn)]

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  servo1.attach(servoPin[0]);  // attaches the servo on servoPin[0] to the servo object - claw
  servo2.attach(servoPin[1]);  // attaches the servo on servoPin[1] to the servo object - left(extend and contract)
  servo3.attach(servoPin[2]);  // attaches the servo on servoPin[2] to the servo object - right (lift up and down)
  servo4.attach(servoPin[3]);  // attaches the servo on servoPin[3] to the servo object - bottom (turn left and right)
}

// the loop routine runs over and over again forever:
void loop() {
// read the input on analog pin A0 to A4:
  for (int i=0; i<4; i++){
    sumValue = 0.0;
    for (int j=0; j<5; j++) {
      readValue = analogRead(i);
      sumValue += readValue;
      delay(1);
    }
    servoRead = sumValue/5.0;
    // adjust the value to the range of 0 to sensorMax (0 - 180 degree)
    servoValue[i] = (int)abs(servoRead-offset)/1000.0*(servoMax+offset);
    // round servoValue per 10 range to servoMax
    servoRead = servoValue[i]/10;
    servoValue[i] = (int)servoRead*10;
    if (servoValue[i]<servoMin) {
      servoValue[i]=servoMin;
    }
    else if (servoValue[i]>servoMax) { 
      servoValue[i]=servoMax;
    };
    
    // print out the value you read:
    Serial.print(servoValue[i]);
    Serial.print(' ');
    
    // move the robot arm according to the values in the potentiometers
    switch (i){
      case 0: {
        // servo1.attach(servoPin[0]);
        if (servoValue[i]<20) {           // limit the claw's turning position 20 to 100
          servoValue[i]=20;               // adjust the open and close claw's position - do not overrun
        }
        else if (servoValue[i]>100) { 
          servoValue[i]=100;
        };
        servo1.write(servoValue[i]);      // adjust the open and close claw's position - do not overrun
        delay(500);
        // adjust the open and close claw's position - do not overrun
        // servo1.detach();               // maintain the tension of the claw
        // delay(500);
      };
      case 1: {
        servo2.attach(servoPin[1]);       // left(extend and contract)
        delay(10);
        servo2.write(servoValue[i]);
        delay(500);   
        servo2.detach();                  // detach servo to save power
        delay(10);
      }; 
      case 2: {
        servo3.attach(servoPin[2]);       // right (lift up and down)
        delay(10);
        servo3.write(servoValue[i]);
        delay(500);   
        servo3.detach();                  // detach servo to save power
        delay(10);
      };  
      case 3: {
        servo4.attach(servoPin[3]);       // bottom (turn left and right)
        delay(10);
        servo4.write(servoValue[i]);
        delay(500);   
        servo4.detach();                  // detach servo to save power
        delay(10);
      };  
    };
  };
  Serial.println();
  delay(500);            // delay in between position for stability
}
