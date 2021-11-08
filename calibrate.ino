
#include <Servo.h>
// twelve servo objects can be created on most boards
Servo servo1;  // create servo object to control a servo

void setup() {
  // put your setup code here, to run once:
  servo1.attach(3);  // attaches the servo on pin 3 to the servo object (Timer 0)
}

void loop() {
  // put your main code here, to run repeatedly:

  // test
  servo1.attach(3);
//  servo1.write(90);
//  delay(500);
  for (int i=10; i<=160; i=i+10){
    servo1.write(i);
    delay(500);
  };
  servo1.detach();
  delay(500);
}
