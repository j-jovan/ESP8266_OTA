#include <Wire.h>
#include "PMS.h"
#include <mySD.h>

int relejUV = 19;

void setup(void) {
  // https://9gag.com/gag/a9nbgyW
  Serial.begin(115200);
  pinMode(relejUV, OUTPUT);
  LCDSetup();
  PMS7003Setup();
  OTASetup();
  LCD_Setup();
  initSDCard();
  ukljuciUV();
  motorPWMInit();
}

void loop(void) {
  PMS::DATA data;
  int seconds;
  int minutes;
  int minutesLast = 0;

  timer(seconds, minutes);

  if (seconds%30 == 0)
    PMS7003ReadData(data);

  if (seconds%5 == 0)
    LCDPMS7003(data);

  if (minutes != minutesLast) {
    upisiNaKarticu();
    minutesLast = minutes;
  }

  Serial.println(senzorPritiska1());
  Serial.println(senzorPritiska2());
  OTAHandleClient();
  motorPWMLoop();
  delay(500);
}
