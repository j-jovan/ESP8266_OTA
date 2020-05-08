//Bug: Ako se kartica izvadi, mora da se pokrene opet inace nece da upisuje na nju.

void initKarticu() {
  Serial.println("Pokretanje SD kartice");

  byte CS = 14;
  byte mosi = 27;
  byte miso = 25;
  byte sck = 26;

  if (!SD.begin(CS, mosi, miso, sck)) {
    Serial.println("Pokretanje neuspesno");
    return;
  }
  Serial.println("Pokretanje uspesno");
  /* Begin at the root "/" */
}


void upisiNaKarticu(int vreme) {

  root = SD.open("/");
  if (root) {
    printDirectory(root, 0);
    root.close();
  } else {
    Serial.println("Greska prilikom otvaranja fajla");
  }

  root = SD.open("vreme.txt", FILE_WRITE);

  if (root) {
    root.println(vreme);
    Serial.print("Upisano na karticu ");
    Serial.println(vreme);
    root.flush();

    root.close();
  } else {
    root.close();
    Serial.println("Greska prilikom probe upisivanja");
  }
  delay(1000);
}

void procitajFajl() {
  root = SD.open("vreme.txt");
  if (root) {
    while (root.available()) {
      Serial.write(root.read());
    }
    root.close();
  } else {
    Serial.println("error opening test.txt");
  }
  Serial.println("done!");
}

void printDirectory(File dir, int numTabs) {

  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }

    Serial.print(entry.name());

    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {

      Serial.print("\t\t");
      Serial.println(entry.size());
    }
    entry.close();
  }
}
