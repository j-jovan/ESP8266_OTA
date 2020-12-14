#define DAC1 25
int serialRead;

// Motor je podesen da prati razliku pritiska u komorama
// I da smanjuje snagu sa porastom razlike pritiska
// Snaga motora je regulisana pomocu diaka/triaka kojim upravljaju LE dioda i fotootpornik.

// Rucno izracunate vrednosti
int snagaMotora[11] = {1, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187};

void motorDacMap() {
  int val = vratiRazlikuPritiska();
  val = map(val, 0, 30, 10, 1);
  dacWrite(DAC1, snagaMotora[val]);

  DPRINTLN("************************* ");
  DPRINT("Snaga motora je: ");
  DPRINT(val * 10);
  DPRINTLN(" %");
  DPRINTLN("************************* ");
}


// Rucna provera rada motora
void motorDacTestManual() {
  if (Serial.available() > 0) {
    int serialRead = Serial.parseInt();
    DPRINTLN("---");
    DPRINTLN("Unesi vrednost.");

    if (serialRead == 0) {
      // Nakon sto Serial.available procita i ispise vrednost
      // Uvek stavi da je vrednost open 0
    }
    else {
      DPRINT("Uneta vrednost je: ");
      DPRINTLN(serialRead);
      dacWrite(DAC1, serialRead);
      DPRINTLN("***");
    }
  }
}

void motorDacTestAuto() {
  int value = 255; // 255 = 3.3V / 128 = 1.65V
  dacWrite(DAC1, value);
  delay(1000);
}
