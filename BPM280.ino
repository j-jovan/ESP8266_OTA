#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BMP280_1_I2C_SDA 21
#define BMP280_1_I2C_SCL 22

#define BMP280_2_I2C_SDA 18
#define BMP280_2_I2C_SCL 5

#define SEALEVELPRESSURE_HPA (1013.25)

TwoWire I2CBME1 = TwoWire(0);
TwoWire I2CBME2 = TwoWire(0);
Adafruit_BME280 bme1;
Adafruit_BME280 bme2;

unsigned long delayTime;

void BPM280_Setup() {
  Serial.begin(115200);
  Serial.println(F("BME280 test"));
  I2CBME1.begin(BMP280_1_I2C_SDA, BMP280_1_I2C_SCL, 100000);
  I2CBME2.begin(BMP280_2_I2C_SDA, BMP280_2_I2C_SCL, 100000);


  bool status;

  status = bme1.begin(0x76, &I2CBME1);
  if (!status) {
    Serial.println("Neuspelo povezivanje sa BMP280 senzorom broj 1, proveri kablove");
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
void BPM280_Loop() {
  BPM1_sve_vrednosti();
  BPM2_sve_vrednosti();
  delay(delayTime);
}

void BPM1_sve_vrednosti() {
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

void BPM2_sve_vrednosti() {
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

float BPM1_pritisak() {
  //  Serial.print("Pritisak = ");
  //  Serial.print(bme1.readPressure() / 100.0F);
  //  Serial.println(" hPa");
  return bme1.readPressure() / 100.0F;
}

float BPM2_pritisak() {
  //  Serial.print("Pritisak = ");
  //  Serial.print(bme2.readPressure() / 100.0F);
  //  Serial.println(" hPa");
  return bme2.readPressure() / 100.0F;
}

void ispisiPritiske() {
  Serial.println(BPM1_pritisak());
  Serial.println(BPM2_pritisak());
}

// granicaZaprljanostiFiltera je broj koji predstavlja kolika razlika pritiska treba biti u obe komore
// da bi se smatralo da su filteri zaprljani
void razlikaPritiska(int granicaZaprljanostiFiltera) {
  if (abs(BPM1_pritisak() - BPM2_pritisak()) > granicaZaprljanostiFiltera) {
    Serial.println("Prljav filter");
  }
}
