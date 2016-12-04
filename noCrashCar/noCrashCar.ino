#include "MeOrion.h"

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
