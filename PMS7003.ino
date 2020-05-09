#define RXD2 34
#define TXD2 35

HardwareSerial SerialPMS(1);
PMS pms(SerialPMS);

void pms7003Setup()
{
  SerialPMS.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pms.passiveMode();
}



void pms7003ReadData(PMS::DATA& data)
{
  pms.wakeUp();

  if (timer() == 30) {
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
    Serial.println("PMS 7003 No Data");
  }
  pms.sleep();
  }
}
