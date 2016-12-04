#include "MeOrion.h"

/*
This code is for an Orion Makeblock (Arduino Uno) board.
My son and I modified a $12 RC car by removing it's remove control
leaving us with the chassis, wheels and two motors.
One motor drives the rear wheels, forward/reverse/stop.
The other drives the front wheels, left/right/center.
We used an ultrasonic sensor mounted to the front to
give a signal when it's going to hit an obstacle.
When it detects an obstacle it stops, turns the wheel
and goes in reverse, then forward straight again (close to a 90deg turn).
My son added a buzzer in reverse all by himself by
refering to the example scripts.
With the top off the car the MakeBlock battery pack and Orion board
sit on top of the chassis. We used zip ties to mount the ultrasonic
detector to the front. The motor drivers we used paper clips to wire
it up (real hack there, should be shielded wires).
*/

MeUltrasonicSensor ultraSensor(PORT_8); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */

MeDCMotor motor1(M1);
MeDCMotor motor2(M2);
uint16_t motorSpeed = 100;
uint16_t turnRadius = 125;
uint16_t distance = 400;
uint16_t triggerDistance = 60;

void setup() {
}

void stop() {
  motor1.stop();
}

void forward() {
  motor1.run(motorSpeed);
}

void reverse() {
  motor1.run(-motorSpeed);
}

void straighten() {
  motor2.stop();
}

void leftTurnReverse() {
  motor2.run(-turnRadius);
  reverse();
}

void rightTurnReverse() {
  motor2.run(turnRadius);
  reverse();
}

void loop() {
  distance = ultraSensor.distanceCm();
  if (distance < triggerDistance) {
    stop();
    leftTurnReverse();
    buzzerOn(); 
    delay(1500);
    stop();
    buzzerOff();
    straighten();
    forward();
  } else {
    forward();
  }
  delay(100);
}

