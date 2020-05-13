#include <Wire.h>
#include "PMS.h"
#include <mySD.h>

void setup(void) {
  // https://9gag.com/gag/a9nbgyW
  Serial.begin(115200);
  LCDSetup();
  PMS7003Setup();
  OTASetup();
  LCD_Setup();
  initSDCard();
  initServo();
  ukljuciUV();
}

void loop(void) {
  int vreme = timer();
  Serial.println(senzorPritiska1());
  Serial.println(senzorPritiska2());
  PMS::DATA data;
  OTAHandleClient();
  delay(1);
  PMS7003ReadData(data);
  LCDPMS7003(data, vreme);
  upisiNaKarticu(vreme);
  kontrolaMotora();
  delay(500);
}
