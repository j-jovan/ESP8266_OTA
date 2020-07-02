#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//Senzor 1
#define BMP280_1_I2C_SDA 21
#define BMP280_1_I2C_SCL 22

//Senzor 2
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
  Serial.println(F("BME280 test"));
  I2CBME1.begin(BMP280_1_I2C_SDA, BMP280_1_I2C_SCL, 100000);
  I2CBME2.begin(BMP280_2_I2C_SDA, BMP280_2_I2C_SCL, 100000);


  bool status;

  status = bme1.begin(0x76, &I2CBME1);
  if (!status) {
    Serial.println("Neuspelo povezivanje sa BMP280 senzorom broj 1, proveri povezivanje");
    while (1);
  }

  status = bme2.begin(0x76, &I2CBME2);
  if (!status) {
    Serial.println("Neuspelo povezivanje sa BMP280 senzorom broj 2, proveri kablove");
    while (1);
  }

  Serial.println("Oba senzora uspesno povezana");
  delayTime = 100;

  Serial.println();
}
void BMP280_Loop() {
  BMP1_sve_vrednosti();
  BMP2_sve_vrednosti();
  delay(delayTime);
}

void BMP1_sve_vrednosti() {
  Serial.print("Temperatura = ");
  Serial.print(bme1.readTemperature());
  Serial.println(" *C");

  Serial.print("Pritisak = ");
  Serial.print(bme1.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Nadmorska visina = ");
  Serial.print(bme1.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Vlaznost vazduha = ");
  Serial.print(bme1.readHumidity());
  Serial.println(" %");

  Serial.println();
}

void BMP2_sve_vrednosti() {
  Serial.print("Temperatura = ");
  Serial.print(bme2.readTemperature());
  Serial.println(" *C");

  Serial.print("Pritisak = ");
  Serial.print(bme2.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Nadmorska visina = ");
  Serial.print(bme2.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Vlaznost vazduha = ");
  Serial.print(bme2.readHumidity());
  Serial.println(" %");

  Serial.println("--------------------");
}

float BMP1_pritisak() {
  //  Serial.print("Pritisak = ");
  //  Serial.print(bme1.readPressure() / 100.0F);
  //  Serial.println(" hPa");
  return bme1.readPressure() / 100.0F;
}

float BMP2_pritisak() {
  //  Serial.print("Pritisak = ");
  //  Serial.print(bme2.readPressure() / 100.0F);
  //  Serial.println(" hPa");
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
    Serial.print("Srednja vrednost prvog senzora: ");
    Serial.println(pritisak1 / brojUzoraka);
    Serial.print("Srednja vrednost drugog senzora: ");
    Serial.println(pritisak2 / brojUzoraka);
    Serial.print("Razlika pritisaka je: ");
    Serial.println(razlikaPritiska);
    pritisakCounter = 0;
    pritisak1 = 0;
    pritisak2 = 0;

  }
}

float vratiRazlikuPritiska() {
  return abs(BMP1_pritisak() - BMP2_pritisak());
}
