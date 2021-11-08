
/*
 This sketch is the testing routine of DOF4 robot arm
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

int servoPin[4] = {3,6,9,10};         // servo PWM pins [claw, left(extend), right(up), bottom(turn)]

void setup() {
  // put your setup code here, to run once:
  servo1.attach(servoPin[0]);  // attaches the servo on servoPin[0] to the servo object (Timer 0)
  servo2.attach(servoPin[1]);  // attaches the servo on servoPin[1] to the servo object (Timer 2)
  servo3.attach(servoPin[2]);  // attaches the servo on servoPin[2] to the servo object (Timer 1)
  servo4.attach(servoPin[3]);  // attaches the servo on servoPin[3] to the servo object (Timer 1)
}

void loop() {
// put your main code here, to run repeatedly:
// pick up the bear
  servo3.attach(servoPin[2]);
  servo3.write(130);                              // go back to the targeted position
  delay(500);
  servo3.detach();                                // detach servo to save power
  delay(500);

// claw
//  servo1.attach(servoPin[0]);
  for (int i=0; i<=100; i=i+10){                  // open the claw and then close the claw
    servo1.write(i);                              // adjust the open and close claw's position - do not overrun
    delay(500);
  };
  delay(2000);                                    // leave the claw open for 2000ms 
  servo1.write(20);                               // close the claw
  delay(500);
//  servo1.detach();                              // skip to maintain the tension of claw
//  delay(500);

// left (extend and contract)
  servo2.attach(servoPin[1]);
  for (int i=10; i>=160; i=i-10){                 // left(extend and then contract)
    servo2.write(i);                              // adjust the extend and contract of left servo's position - do not overrun
    delay(500);
  };
  servo2.write(90);                               // go back to the desired position
  delay(500);
  servo2.detach();                                // detach servo to save power
  delay(500);

// right (lift up and down)
  servo3.attach(servoPin[2]);
  for (int i=40; i<=120; i=i+10){                  // right(up and then down)
    servo3.write(i);                              // adjust the lift up and down of right servo's position - do not overrun
    delay(500);
  };
  servo3.write(60);                               // go back to the desired position
  delay(500);
  servo3.detach();                                // detach servo to save power
  delay(500);

//  // bottom
  servo4.attach(servoPin[3]);
  for (int i=0; i<=160; i=i+10){                  // bottom (left and then right)
    servo4.write(i);                              // adjust the turn left and right of bottom servo's position - do not overrun
    delay(500);
  };
  servo4.write(100);                               // go back to the idle position
  delay(500);
  servo4.detach();                                // detach servo to save power
  delay(1000);
}
