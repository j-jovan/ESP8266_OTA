#include <Servo.h>

Servo servo2;
const int servoPin = 23;

void initServo() {
  servo2.attach(servoPin);
}

void servoControl(int stepeni) {
  for (int pos = 0; pos <= stepeni; pos += 1) {
    servo2.write(pos);
    Serial.println(pos);
  }
}
void kontrolaMotora() {
  if (600 < senzorPritiska1() < 700)
    servo2.write(90);
  if (700 < senzorPritiska1() < 800)
    servo2.write(100);
  if (800 < senzorPritiska1() < 900)
    servo2.write(110);
  if (900 < senzorPritiska1() < 1000)
    servo2.write(120);

}
