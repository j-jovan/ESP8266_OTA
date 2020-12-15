/*
    Srbija Hakuje Koronu
    Sterilizator Prostorije

    Kod napisan za potrebe Sterilizatora prostorije
    Razvijen na "Srbija Hakuje Koronu" Hakatonu
    Beograd, Jun 2020

    ESP board link:
    https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json


    Koriscene biblioteke:
    https://github.com/fu-hsi/PMS
    https://github.com/nhatuan84/esp32-micro-sdcard
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/Adafruit_BME280_Library
    https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

    Koriscene elektronske komponente:
    1. ESP32 DevKit V1
    2. BMP280 3.3v x2
    3. LCD Display 20x4
    4. PMS 7003 Particle Sensor
    5. MicroSD Card Reader i microSD kartica (256mb minimum)
    6. Motor CBM/2-146/180 - 380W (1090m3/H, 2000 RPM)
    7. UV Sijalice (Germicidne) x6
    8. Razna sitna elektronika i plasticni delovi

    Dodatne komponente:
    9. HEPA filter
    10. Predfilter x2 (Predfilteri upijaju krupnije cestice kako bi HEPA trajao duze)

    Opis uredjaja:
    Uredjaj je podeljen na dve komore (gornju i donju) pomocu dva predfiltera (10) i HEPA filtera (9).
    Vazduh ulazi kroz resetku na gornjoj komori, prolazi kroz dva predfiltera (10) i onda ga UV (7) sterilise.
    Nakon toga prolazi kroz HEPA filter (9), pa sledi jos jedna sterilizaciju UV (7) lampama pre napustanja uredjaja.
    U donjoj komori uredjaja se nalazi motor (6) koji uvlaci provlaci vazduh kroz ceo uredjaj.

    Info:
    Prvobitni plan je bio da koristimo cip iz Arduino Uno ili Arduino Pro Mini/Nano, ali nije bilo dovoljno memorije za kod, te smo uzeli ESP32
    LCD Displej prikazuje podatke iz uredjaja korisnicima
    Podaci iz senzora cestica se cuvaju u micoSD kartici, kao i radno vreme uredjaja
    Senzor pritiska prati pritisak u dve komore i obavestava korisnika ukoliko je razlika prevelika, jer to znaci da je vreme za zamenu filtera.
    Radni vek UV lampi je 50.000 sati.



*/

#include <Wire.h>
#include "PMS.h"
#include <mySD.h>

#define PMS_READ_INTERVAL 1

#define DEBUGG
#ifdef DEBUGG
#define DPRINT(x) Serial.print(x)      //Uncomment to enable debugging
#define DPRINTLN(x) Serial.println(x)  //Uncomment to enable debugging
#elif
#define DPRINT(x) ;
#define DPRINTLN(x) ;
#endif

int relejUV = 19;
int prekidac = 33;
bool ukljuciUredjaj = false;

void setup(void) {
  // https://9gag.com/gag/a9nbgyW
  Serial.begin(115200);
  pinMode(relejUV, OUTPUT);
  pinMode(prekidac, INPUT);
  LCD_Setup();
  PMS7003_Setup();
  OTA_Setup();
  LCD_SHK_Message();
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
    //BMP280_Setup();
  }

  // Proveri i postavi snagu motora na svakih 30 sekundi
  //    if (seconds % 30 == 0) {
  //      motorDacMap();
  //    }

  OTAHandleClient();

  delay(500);
  DPRINTLN("--------------------");
}
