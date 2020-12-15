#include <Adafruit_BME280.h>

// Senzor 1
#define BMP280_1_I2C_SDA 21
#define BMP280_1_I2C_SCL 22

// Senzor 2
#define BMP280_2_I2C_SDA 5
#define BMP280_2_I2C_SCL 18

#define SEALEVELPRESSURE_HPA (1013.25)

TwoWire I2CBME1 = TwoWire(0);
TwoWire I2CBME2 = TwoWire(1);

Adafruit_BME280 bme1;
Adafruit_BME280 bme2;

unsigned long delayTime;

void BMP280_Setup() {
  Serial.begin(115200);
  DPRINTLN(F("BME280_Setup start"));
  I2CBME1.begin(BMP280_1_I2C_SDA, BMP280_1_I2C_SCL, 100000);
  I2CBME2.begin(BMP280_2_I2C_SDA, BMP280_2_I2C_SCL, 100000);


  bool status;

  status = bme1.begin(0x76, &I2CBME1);
  if (!status) {
    DPRINTLN("Neuspelo povezivanje sa BMP280 senzorom broj 1 (gornja komora), proveri povezivanje");
    while (1);
  }

  status = bme2.begin(0x76, &I2CBME2);
  if (!status) {
    DPRINTLN("Neuspelo povezivanje sa BMP280 senzorom broj 2 (donja komora), proveri kablove");
    while (1);
  }

  DPRINTLN("Oba senzora uspesno povezana");
  delayTime = 100;

  DPRINTLN("BMP280 kraj");
  DPRINTLN("------------------");
}
void BMP280_Loop() {
  BMP1_sve_vrednosti();
  BMP2_sve_vrednosti();
  delay(delayTime);
}

void BMP1_sve_vrednosti() {
  DPRINT("Temperatura = ");
  DPRINT(bme1.readTemperature());
  DPRINTLN(" *C");

  DPRINT("Pritisak = ");
  DPRINT(bme1.readPressure() / 100.0F);
  DPRINTLN(" hPa");

  DPRINT("Nadmorska visina = ");
  DPRINT(bme1.readAltitude(SEALEVELPRESSURE_HPA));
  DPRINTLN(" m");

  DPRINT("Vlaznost vazduha = ");
  DPRINT(bme1.readHumidity());
  DPRINTLN(" %");
  DPRINTLN("------------------");
}

void BMP2_sve_vrednosti() {
  DPRINT("Temperatura = ");
  DPRINT(bme2.readTemperature());
  DPRINTLN(" *C");

  DPRINT("Pritisak = ");
  DPRINT(bme2.readPressure() / 100.0F);
  DPRINTLN(" hPa");

  DPRINT("Nadmorska visina = ");
  DPRINT(bme2.readAltitude(SEALEVELPRESSURE_HPA));
  DPRINTLN(" m");

  DPRINT("Vlaznost vazduha = ");
  DPRINT(bme2.readHumidity());
  DPRINTLN(" %");
  DPRINTLN("--------------------");
}

float BMP1_pritisak() {
  DPRINT("Pritisak = ");
  DPRINT(bme1.readPressure() / 100.0F);
  DPRINTLN(" hPa");
  return bme1.readPressure() / 100.0F;
}

float BMP2_pritisak() {
  DPRINT("Pritisak = ");
  DPRINT(bme2.readPressure() / 100.0F);
  DPRINTLN(" hPa");
  return bme2.readPressure() / 100.0F;
}

float pritisak1 = 0;
float pritisak2 = 0;
int pritisakCounter = 0;
int brojUzoraka = 10;
float razlikaPritiska = 0;

void srednjaVrednostBMP() {
  pritisak1 += BMP1_pritisak();
  pritisak2 += BMP2_pritisak();
  razlikaPritiska = abs(pritisak1 - pritisak2) / brojUzoraka;
  pritisakCounter++;
  if (pritisakCounter == brojUzoraka) {
    DPRINTLN("--------------------");
    DPRINT("Srednja vrednost prvog senzora: ");
    DPRINTLN(pritisak1 / brojUzoraka);
    DPRINT("Srednja vrednost drugog senzora: ");
    DPRINTLN(pritisak2 / brojUzoraka);
    DPRINT("Razlika pritiska je: ");
    DPRINTLN(razlikaPritiska);
    DPRINTLN("--------------------");
    pritisakCounter = 0;
    pritisak1 = 0;
    pritisak2 = 0;

  }
}

float vratiRazlikuPritiska() {
  DPRINTLN(abs(BMP1_pritisak() - BMP2_pritisak()));
  return abs(BMP1_pritisak() - BMP2_pritisak());
}
