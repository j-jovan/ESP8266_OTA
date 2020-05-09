#include <LiquidCrystal_I2C.h>

#define LCD_SDA 33
#define LCD_SCL 32

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
  lcd.print("Pokretanje ");
  
  for (int i = 0; i <= 9; i++) {
    lcd.print(".");
    delay(100);
  }
}

void pmsSenzorDisplej(PMS::DATA& data, int timer) {
  if (timer == 30) {
    lcd.begin(); //Ako displej nije povezan, ne radi ostali kod. Treba neki try catch
    lcd.backlight();
    lcd.setCursor (0, 0);
    lcd.print("Konc pm1:   " + String(data.PM_AE_UG_1_0) + " mg/m3");
    lcd.setCursor (0, 1);
    lcd.print("Konc pm2.5: " + String(data.PM_AE_UG_2_5) + " mg/m3");
    lcd.setCursor (0, 2);
    lcd.print("Konc pm10:  " + String(data.PM_AE_UG_10_0) + " mg/m3");
    lcd.setCursor (0, 3);
    lcd.print("Snaga motora ?%");
  }
}
