#include <Wire.h>
#include "PMS.h"
#include <mySD.h>

void setup(void) {
  //https://9gag.com/gag/a9nbgyW

  Serial.begin(115200);
  LCDSetup();
  pms7003Setup();
  OTASetup();

  pocetnaPoruka();
  initKarticu();
  //procitajFajl();
}

void loop(void) {
  PMS::DATA data;
  OTAHandleClient();
  delay(1);
  //pms7003ReadData(data);
  //pmsSenzorDisplej(data);
  upisiNaKarticu(timer());
  delay(500);
}
