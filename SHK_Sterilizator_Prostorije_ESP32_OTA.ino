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
  inicijalizacijaIPisanje();
  procitajFajl();
}

void loop(void) {
  PMS::DATA data;
  OTAHandleClient();
  delay(1);
  data = pms7003ReadData();
  pmsSenzorDisplej(data);
}
