#include <Servo.h>

Servo servoMotor;
const int servoPin = 23;

void initServo() {
  servoMotor.attach(servoPin);
}

void servoControl(int stepeni) {
  for (int pos = 0; pos <= stepeni; pos += 1) {
    servoMotor.write(pos);
    Serial.println(pos);
  }
}

void kontrolaMotora() {
  float motor = map(senzorPritiska1(), 1, 5, 0, 180);
  servoMotor.write(motor);
  Serial.print("Servo motor: ");
  Serial.println(motor);
}
