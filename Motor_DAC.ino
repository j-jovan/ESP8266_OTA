#define DAC1 25

int snagaMotora[11] = {1, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187};  // Rucno izracunate vrednosti

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

void motorDacTest() {
  int value = 255; // 255 = 3.3V / 128 = 1.65V
  dacWrite(DAC1, value);
  delay(1000);
}
