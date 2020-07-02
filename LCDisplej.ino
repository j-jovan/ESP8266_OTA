#include <LiquidCrystal_I2C.h>

#define LCD_SCL 4
#define LCD_SDA 15

LiquidCrystal_I2C lcd(0x27, 20, 4);

//Ako displej nije povezan, ne radi ostali kod. Treba neki try catch
void LCD_Setup() {
  Wire.begin(LCD_SDA, LCD_SCL );
}

void LCD_Start() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print("Srbija Hakuje Koronu");
  lcd.setCursor (4, 1);
  lcd.print("Sterilizator");
  lcd.setCursor (5, 2);
  lcd.print("Prostorije");
  lcd.setCursor (0, 3);
  lcd.print("Pokretanje...");
}

void LCD_PMS7003(PMS::DATA& data) {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print("Konc pm1:   " + String(data.PM_AE_UG_1_0) + " mg/m3");
  lcd.setCursor (0, 1);
  lcd.print("Konc pm2.5: " + String(data.PM_AE_UG_2_5) + " mg/m3");
  lcd.setCursor (0, 2);
  lcd.print("Konc pm10:  " + String(data.PM_AE_UG_10_0) + " mg/m3");
  lcd.setCursor (0, 3);
  lcd.print("Radno vreme: ");
  int brojSati = radnoVreme() / 60;
  int brojMinuta = radnoVreme() - brojSati * 60;
  lcd.print(brojSati);
  lcd.print("s:");
  lcd.print(brojMinuta);
  lcd.print("m");
}

void LCD_Debug(int i) {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print(i);
  lcd.setCursor (0, 1);
  lcd.print("");
  lcd.setCursor (5, 2);
  lcd.print("");
  lcd.setCursor (0, 3);
  lcd.print("");
}

void LCD_Debug(String i) {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print(i);
  lcd.setCursor (0, 1);
  lcd.print("");
  lcd.setCursor (5, 2);
  lcd.print("");
  lcd.setCursor (0, 3);
  lcd.print("");
}

void LCD_Debug(String i, String z) {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print(i);
  lcd.setCursor (0, 1);
  lcd.print(z);
  lcd.setCursor (5, 2);
  lcd.print("");
  lcd.setCursor (0, 3);
  lcd.print("");
}

// Obavestavanje kad se priblizava servis uredjaja
//void LCD_Upozorenje(int x) {
//  lcd.begin();
//  lcd.backlight();
//  lcd.setCursor (0, 0);
//  lcd.print("Konc pm1:   " + String(data.PM_AE_UG_1_0) + " mg/m3");
//  lcd.setCursor (0, 1);
//  lcd.print("Konc pm2.5: " + String(data.PM_AE_UG_2_5) + " mg/m3");
//  lcd.setCursor (0, 2);
//  lcd.print("Konc pm10:  " + String(data.PM_AE_UG_10_0) + " mg/m3");
//  lcd.setCursor (0, 3);
//  int brojSati = radnoVreme() / 60;
//  int brojMinuta = radnoVreme() - brojSati * 60;
//  lcd.print(x - brojSati);
//  lcd.print(" sati do servisa");
//}
