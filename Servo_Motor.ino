#include <Servo.h>

Servo servo2;
const int servoPin = 23;

void initServo() {
  servo2.attach(servoPin);
}

void servoControl2() {
  for (int pos = 0; pos <= 180; pos += 1) {
    servo2.write(pos);
    Serial.println(pos);
    delay(20);
  }
  //  for (int pos = 180; pos >= 0; pos -= 1) {
  //    servo2.write(pos);
  //    Serial.println(pos);
  //    delay(20);
  //  }
}

void servoControl() {
  for (int pos = 0; pos <= 180; pos += 1) {
    servo2.write(pos);
    Serial.println(pos);
  }
  delay(20);
}
