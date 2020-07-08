#include <Wire.h>
#include "PMS.h"
#include <mySD.h>

#define PMS_READ_INTERVAL 5

int relejUV = 19;

void setup(void) {
  // https://9gag.com/gag/a9nbgyW
  Serial.begin(115200);
  pinMode(relejUV, OUTPUT);
  LCD_Setup();
  PMS7003_Setup();
  OTA_Setup();
  LCD_Start();
  init_SDCard();
  //ukljuciUV();
  BMP280_Setup();
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
    LCD_PMS7003(data);
    PMSMinutesRead += PMS_READ_INTERVAL;
  }

  if (minutes == SDMinutesWrite) {
    upisiNaKarticu();
    SDMinutesWrite++;
    //PMS7003_Setup();
    //LCD_PMS7003(data);
    BMP280_Setup();
  }

  // Proveri i postavi snagu motora na svakih 10 sekundi
  if (seconds % 20 == 0) {
    motorDacMap();
  }
  if (seconds == 30) {
    //LCD_Pritisak();
    
    
  }

  // OTA Handler
  OTAHandleClient();

  srednjaVrednostBMP();
  Serial.print("Pritisak 1 ");
  Serial.println(BMP1_pritisak());
  Serial.print("Pritisak 2 ");
  Serial.println(BMP2_pritisak());

  Serial.println(vratiRazlikuPritiska());
  delay(500);
  Serial.println("--------------------");


}
