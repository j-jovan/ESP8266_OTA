/*
    Srbija Hakuje Koronu
    Sterilizator Prostorije

    Kod napisan za potrebe Sterilizatora prostorije koji je razvijen na Srbija Hakuje Koronu Hakatonu
    Beograd, Jun 2020

    Koriscene komponente:
    ESP32 DevKit V1
    BMP280 3.3v x2
    LCD Display 20x4
    PMS 7003 Particle Sensor
    MicroSD Card Reader
    Motor CBM/2-146/180 - 380W (1090m3/H, 2000 RPM)
    UV Sijalice Germicidne x6
    Razna sitna elektronika i plasticni delovi

    Koriscene biblioteke:
    https://github.com/fu-hsi/PMS
    https://github.com/nhatuan84/esp32-micro-sdcard/blob/master/mySD.h
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/Adafruit_BME280_Library
    https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

*/

#include <Wire.h>
#include "PMS.h"
#include <mySD.h>

#define PMS_READ_INTERVAL 5

#define DEBUGG
#ifdef DEBUGG
//#define DPRINT(x) Serial.print(x)      //Uncomment to enable debugging
//#define DPRINTLN(x) Serial.println(x)  //Uncomment to enable debugging
//#elif
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
