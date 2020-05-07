#define RXD2 34
#define TXD2 35

HardwareSerial SerialPMS(1);
PMS pms(SerialPMS);

void pms7003Setup()
{
  SerialPMS.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pms.passiveMode();
}

PMS::DATA pms7003ReadData()
{
  PMS::DATA data;
  pms.wakeUp();
  delay(3000);
  pms.requestRead();


  if (pms.readUntil(data))
  {
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);
    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);
    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);
  }
  else
  {
    Serial.println("No data.");
  }
  pms.sleep();
  delay(6000);

  return data;
}
