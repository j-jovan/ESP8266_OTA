#include <Wire.h>
#include "PMS.h"
#include <mySD.h>

#define PMS_READ_INTERVAL 5

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
  unsigned int seconds;
  unsigned int minutes;
  static unsigned int SDMinutesWrite = 1;
  static unsigned int PMSMinutesOn = 0;
  static unsigned int PMSMinutesRead = 1;
  
  timer(seconds, minutes);

  if (minutes == PMSMinutesOn) {
    PMS7003WakeUp();
    PMSMinutesOn += PMS_READ_INTERVAL;
  }
  if (minutes == PMSMinutesRead) {
    PMS7003ReadData(data);
    PMS7003Sleep();
    LCDPMS7003(data);
    PMSMinutesRead += PMS_READ_INTERVAL;
  }

  if (minutes == SDMinutesWrite) {
    upisiNaKarticu();
    LCDPMS7003(data);
    SDMinutesWrite++;
  }

  Serial.println(senzorPritiska1());
  Serial.println(senzorPritiska2());
  OTAHandleClient();
  motorPWMLoop();
  delay(500);
}
