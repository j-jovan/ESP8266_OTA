// Biblioteke
// https://github.com/esp8266/Arduino/blob/master/libraries/Wire/Wire.h
// https://github.com/fu-hsi/PMS
// https://github.com/nhatuan84/esp32-micro-sdcard/blob/master/mySD.h
// https://github.com/adafruit/Adafruit_Sensor  //mozda ne treba
// https://github.com/adafruit/Adafruit_BME280_Library
// https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

#include <Wire.h>
#include "PMS.h"
#include <mySD.h>

#define PMS_READ_INTERVAL 5
#define DEBUGG
#ifdef DEBUGG
#define DPRINT(x) Serial.print(x)
#define DPRINTLN(x) Serial.println(x) 
#elif
#define DPRINT(x) ;
#define DPRINTLN(x) ;
#endif

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
  ukljuciUV();
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
    upisiPMSData(data);
    PMSMinutesRead += PMS_READ_INTERVAL;
  }

  if (minutes == SDMinutesWrite) {
    upisiNaKarticu();
    SDMinutesWrite++;
    PMS7003_Setup();
    LCD_PMS7003(data);
    BMP280_Setup();
  }

  // Proveri i postavi snagu motora na svakih 10 sekundi
  if (seconds % 20 == 0) {
    motorDacMap();
  }
  if (seconds == 30) {
    //    LCD_Pritisak();
    //    BMP280_Setup();

  }

  OTAHandleClient();

  srednjaVrednostBMP();
  DPRINT("Pritisak 1 ");
  DPRINTLN(BMP1_pritisak());
  DPRINT("Pritisak 2 ");
  DPRINTLN(BMP2_pritisak());
  DPRINTLN(vratiRazlikuPritiska());
  
  delay(500);
  DPRINTLN("--------------------");


}
