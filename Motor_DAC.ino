#define DAC1 25

int snagaMotora[11] = {1, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187};
//int pritisakMotora[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 10};

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


// Obsolite, za brisanje.
//void motorDACLoop() {
//
//  if (vratiRazlikuPritiska() >= pritisakMotora[0] && vratiRazlikuPritiska() <= pritisakMotora[1]) {
//    dacWrite(DAC1, snagaMotora[10]);
//    DPRINTLN("Snaga motora je 100%");
//  }
//  if (vratiRazlikuPritiska() > pritisakMotora[2] && vratiRazlikuPritiska() <= pritisakMotora[3]) {
//    dacWrite(DAC1, snagaMotora[9]);
//    DPRINTLN("Snaga motora je 90%");
//  }
//  if (vratiRazlikuPritiska() > pritisakMotora[4] && vratiRazlikuPritiska() <= pritisakMotora[5]) {
//    dacWrite(DAC1, snagaMotora[7]);
//    DPRINTLN("Snaga motora je 80%");
//  }
//  if (vratiRazlikuPritiska() > pritisakMotora[6] && vratiRazlikuPritiska() <= pritisakMotora[7]) {
//    dacWrite(DAC1, snagaMotora[6]);
//    DPRINTLN("Snaga motora je 70%");
//  }
//  if (vratiRazlikuPritiska() > pritisakMotora[8] && vratiRazlikuPritiska() <= pritisakMotora[9]) {
//    dacWrite(DAC1, snagaMotora[5]);
//    DPRINTLN("Snaga motora je 60%");
//  }
//  if (vratiRazlikuPritiska() > pritisakMotora[10] && vratiRazlikuPritiska() <= pritisakMotora[11]) {
//    dacWrite(DAC1, snagaMotora[4]);
//    DPRINTLN("Snaga motora je 50%");
//  }
//  if (vratiRazlikuPritiska() > pritisakMotora[12] && vratiRazlikuPritiska() <= pritisakMotora[13]) {
//    dacWrite(DAC1, snagaMotora[3]);
//    DPRINTLN("Snaga motora je 40%");
//  }
//  if (vratiRazlikuPritiska() > pritisakMotora[14] && vratiRazlikuPritiska() <= pritisakMotora[15]) {
//    dacWrite(DAC1, snagaMotora[2]);
//    DPRINTLN("Snaga motora je 30%");
//  }
//  if (vratiRazlikuPritiska() > pritisakMotora[16] && vratiRazlikuPritiska() <= pritisakMotora[17]) {
//    dacWrite(DAC1, snagaMotora[1]);
//    DPRINTLN("Snaga motor je 20%");
//  }
//  if (vratiRazlikuPritiska() > pritisakMotora[18] && vratiRazlikuPritiska() <= pritisakMotora[19]) {
//    dacWrite(DAC1, snagaMotora[0]);
//    DPRINTLN("Snaga motora je 10%");
//  }
