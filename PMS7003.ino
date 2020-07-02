#define RXD2 39
#define TXD2 34

HardwareSerial SerialPMS(1);
PMS pms(SerialPMS);

void PMS7003_Setup() {
  SerialPMS.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pms.passiveMode();
}

void PMS7003WakeUp() {
  pms.wakeUp();
  Serial.println("PMS Wake Up");
}

void PMS7003Sleep() {
  pms.sleep();
  Serial.println("PMS Sleep");
}

void PMS7003ReadData(PMS::DATA& data) {
  pms.requestRead();
  if (pms.readUntil(data))
  {
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);
    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);
    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);
    //delay(20);
  } else {
    Serial.println("PMS ne vraca podatke");
  }
}
