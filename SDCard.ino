#define SD_MISO 26
#define SD_SCK 27
#define SD_MOSI 14
#define SD_CS 12


File root;

void initSDCard() {
  Serial.print("Inicijalizacija SD kartice...");
  if (!SD.begin(SD_CS, SD_MOSI, SD_MISO, SD_SCK)) {
    Serial.println("neuspesna");
    return;
  }
  Serial.println("uspesna");
  root = SD.open("/");
  if (root) {
    printDirectory(root, 0);
    root.close();
  } else {
    Serial.println("Greska prilikom otvaranja fajla");
  }
  delay(1000);
}

void upisiNaKarticu(int i) {
  if (i == 60) {
    root = SD.open("vreme.txt", FILE_WRITE);
    if (root) {
      root.print("0");
      root.flush();
      Serial.println("Uspesno upisivanje");
      root.close();
    }
    else {

      Serial.println("Greska prilikom upisivanja");
    }
  }
}

void procitajFajl() {
  root = SD.open("vreme.txt");
  if (root) {
    while (root.available()) {
      Serial.write(root.read());
    }
    root.close();
  } else {
    Serial.println("Greska prilikom otvaranja fajla");
  }

  Serial.println("Uradjeno!");
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

int radnoVreme() {
  root = SD.open("vreme.txt");
  if (root) {
    if (root.available()) {
      return root.size();
    }
    root.close();
  } else {
    Serial.println("Timer ne radi");
  }
}
