#include <Wire.h>
#include "PMS.h"
#include <mySD.h>

void setup(void) {
  // https://9gag.com/gag/a9nbgyW
  Serial.begin(115200);
  LCDSetup();
  pms7003Setup();
  OTASetup();
  pocetakLCD();
  initKarticu();
  //procitajFajl();

}

void loop(void) {
  int vreme = timer();
  PMS::DATA data;
  OTAHandleClient();
  delay(1);
  pms7003ReadData(data);
  pmsLCD(data, vreme);
  upisiNaKarticu(vreme);
  delay(500);
}
