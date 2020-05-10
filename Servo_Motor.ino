#include <Servo.h>

Servo servo2;
const int servoPin = 23;

void servoInit() {
  servo2.attach(servoPin);

}

void servoControl() {

  for (int pos = 0; pos <= 90; pos += 1) {
    servo2.write(pos);
    Serial.println(pos);
    delay(20);
  }
  for (int pos = 90; pos >= 0; pos -= 1) {
    servo2.write(pos);
    Serial.println(pos);
    delay(50);
  }
}
