#define DAC1 25
int serialRead;

// Motor je podesen da prati razliku pritiska u komorama
// I da smanjuje snagu sa porastom razlike pritiska
// Snaga motora je regulisana pomocu diaka/triaka kojim upravljaju LE dioda i fotootpornik.

// Rucno izracunate vrednosti
int snagaMotora[7] = {1, 153, 154, 155, 156, 158, 200};

void motorDacMap() {
  int val = vratiRazlikuPritiska();
  val = map(val, 0, 30, 7, 1);  // Ako razlika 0, snaga motora 7, ako razlika
  dacWrite(DAC1, snagaMotora[val]);

  DPRINTLN("************************* ");
  DPRINT("Snaga motora je: ");
  DPRINT(val);
  DPRINTLN("************************* ");
}


// Provera rada motora sa rucnim unosenjem vrednosti preko Serial Monitora
void motorDacTestManual() {
  if (Serial.available() > 0) {
    int serialRead = Serial.parseInt();
    DPRINTLN("----------------------------");
    DPRINTLN("Unesi vrednost");

    if (serialRead == 0) {
      // Nakon sto Serial.available procita i ispise vrednost
      // Uvek stavi da je vrednost open 0
    }
    else {
      DPRINT("Uneta vrednost je: ");
      DPRINTLN(serialRead);
      dacWrite(DAC1, serialRead);
      DPRINTLN("----------------------------");
    }
  }
}

// Automatska provera rada motora tako sto ESP32 sam pojaca snagu motora od minimuma do maksimuma
void motorDacTestAuto() {
  // 255 = 3.3V / 128 = 1.65V
  for (int i = 0; i <= 255; i++) {
    dacWrite(DAC1, i);
    delay(1000);
  }
}
