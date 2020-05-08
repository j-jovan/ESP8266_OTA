<<<<<<< HEAD
void pocetnaPoruka() {
  lcd.begin(); //Ako displej nije povezan, ne radi ostali kod. Treba neki try catch
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print("Srbija Hakuje Koronu");
  lcd.setCursor (4, 1);
  lcd.print("Sterilizator");
  lcd.setCursor (5, 2);
  lcd.print("Prostorije");
  lcd.setCursor (0, 3);
  lcd.print("Pokretanje");
  delay(1000);
  for (int i = 0; i <= 9; i++) {
    lcd.print(".");
    delay(1);
  }
}

void pmsSenzorDisplej() {
  lcd.begin(); //Ako displej nije povezan, ne radi ostali kod. Treba neki try catch
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print("Konc pm1:   " + String(data.PM_AE_UG_1_0)+" mg/m3");
  lcd.setCursor (0, 1);
  lcd.print("Konc pm2.5: " + String(data.PM_AE_UG_2_5)+" mg/m3");
  lcd.setCursor (0, 2);
  lcd.print("Konc pm10:  " + String(data.PM_AE_UG_10_0)+" mg/m3");
  lcd.setCursor (0, 3);
  lcd.print("Snaga motora ?%");
}
=======
#include <LiquidCrystal_I2C.h>

#define LCD_SDA 32
#define LCD_SCL 33

LiquidCrystal_I2C lcd(0x27, 20, 4);

void LCDSetup()
{
    Wire.begin(LCD_SCL, LCD_SDA);
}

void pocetnaPoruka() {
  lcd.begin(); //Ako displej nije povezan, ne radi ostali kod. Treba neki try catch
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print("Srbija Hakuje Koronu");
  lcd.setCursor (4, 1);
  lcd.print("Sterilizator");
  lcd.setCursor (5, 2);
  lcd.print("Prostorije");
  lcd.setCursor (0, 3);
  lcd.print("Pokretanje");
  delay(1000);
  for (int i = 0; i <= 9; i++) {
    lcd.print(".");
    delay(100);
  }
}

void pmsSenzorDisplej(PMS::DATA& data) {
  lcd.begin(); //Ako displej nije povezan, ne radi ostali kod. Treba neki try catch
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print("Konc pm1:   " + String(data.PM_AE_UG_1_0)+" mg/m3");
  lcd.setCursor (0, 1);
  lcd.print("Konc pm2.5: " + String(data.PM_AE_UG_2_5)+" mg/m3");
  lcd.setCursor (0, 2);
  lcd.print("Konc pm10:  " + String(data.PM_AE_UG_10_0)+" mg/m3");
  lcd.setCursor (0, 3);
  lcd.print("Snaga motora ?%");
}
>>>>>>> 0d615caecf7a0b03f917186cdef9e8a53c229823
