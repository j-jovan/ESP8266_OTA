#include <LiquidCrystal_I2C.h>

#define LCD_SCL 4
#define LCD_SDA 15

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Pokretanje I2C
void LCD_Setup() {
  DPRINTLN("LCD_Setup() start");
  Wire.begin(LCD_SDA, LCD_SCL );
}

// Pokretanje LCD-a i pozdravna poruka
void LCD_SHK_Message() {
  DPRINTLN("LCD_Start() start");
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print("Srbija Hakuje Koronu");
  lcd.setCursor (4, 1);
  lcd.print("Sterilizator");
  lcd.setCursor (5, 2);
  lcd.print("Prostorije");
  lcd.setCursor (5, 3);
  lcd.print("Pokretanje");
  delay(10000);
  lcd.setCursor (0, 0);
  lcd.print("Podaci za 50 sekundi");

}

// Prikazi na LCD podatke sa PMS7003 i ukupan broj radnih sati uredjaja
void LCD_PMS7003(PMS::DATA& data) {
  DPRINTLN("LCD_PMS7003 start");
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
  DPRINTLN("LCD_PMS7003 kraj");
}

void LCD_Filteri() {
  DPRINTLN("LCD_Filteri() start");
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print("Zaprljani filteri");
}

// Prikazi na LCD pritisak u komorama uređaja, vreme do servisa i radno vreme
// Ne radi
// void LCD_Pritisak() {
//   DPRINTLN("LCD_Pritisak() start");
//   int brojSati = radnoVreme() / 60;
//   int brojMinuta = radnoVreme() - brojSati * 60;
//   lcd.begin();
//   lcd.backlight();
//   lcd.setCursor (0, 0);
//   lcd.print("Pritisak kom 1: ");
//   lcd.print(BMP1_pritisak());
//   lcd.print(" mBar");
//   lcd.setCursor (0, 1);
//   lcd.print("Pritisak kom 2: ");
//   lcd.print(BMP2_pritisak());
//   lcd.print(" mBar");
//   lcd.setCursor (0, 2);
//   int vremeServis = 50000 - brojSati;
//   lcd.print("Servis za: ");
//   lcd.print(vremeServis);
//   lcd.print(" h");
//   lcd.setCursor (0, 3);
//   lcd.print("Radno vreme: ");
//   lcd.print(brojSati);
//   lcd.print("s:");
//   lcd.print(brojMinuta);
//   lcd.print("m");
//   DPRINTLN("LCD_Pritisak() kraj");
// }


// Set debug statementa
// Prima kao parametre null, int i String
void LCD_Debug() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print("");
  lcd.setCursor (0, 1);
  lcd.print("123456789");
  lcd.setCursor (5, 2);
  lcd.print("asdfghjkl");
  lcd.setCursor (0, 3);
  lcd.print("zxcvbnmmnb");
}
void LCD_Debug(int i) {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print(i);
  lcd.setCursor (0, 1);
  lcd.print(i);
  lcd.setCursor (0, 2);
  lcd.print(i);
  lcd.setCursor (0, 3);
  lcd.print(i);
}
void LCD_Debug(String i) {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print(i);
  lcd.setCursor (0, 1);
  lcd.print(i);
  lcd.setCursor (0, 2);
  lcd.print(i);
  lcd.setCursor (0, 3);
  lcd.print(i);
}

void LCD_Test() {
  int column = 0;
  int row = 0;

  lcd.begin();
  lcd.backlight();
  for (row = 0; row <= 3; row++) {
    for (column = 0; column <= 19; column++) {
      lcd.setCursor (column, row);
      lcd.print("*");
      delay(100);
      lcd.clear();
    }
  }
}

void LCD_Clear() {
  lcd.begin();
  lcd.noBacklight();
  lcd.clear();
}

void LCD_Shutdown() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor (0, 0);
  lcd.print("    Sterilizator");
  lcd.setCursor (0, 1);
  lcd.print("         se");
  lcd.setCursor (0, 2);
  lcd.print("     iskljucuje");
  lcd.setCursor (0, 3);
  lcd.print("");
  delay(10000);
  lcd.noBacklight();
  lcd.clear();

}

// Obavestavanje kad se priblizava servis uredjaja
// Ne radi
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
