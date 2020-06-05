#define SD_MISO 26
#define SD_SCK 14
#define SD_MOSI 27
#define SD_CS 12

File root;
static const char* filename = "vreme.txt";
static unsigned long rVreme;

void initSDCard() {
  Serial.print("Inicijalizacija SD kartice...");
  if (!SD.begin(SD_CS, SD_MOSI, SD_MISO, SD_SCK)) {
    Serial.println("neuspesna");
    return;
  }
  Serial.println("uspesna");
  root = SD.open("/");
  if (!root) {
    Serial.println("Greska prilikom otvaranja fajla");
    return;
  }

  printDirectory(root, 0);
  root.close();

  rVreme = radnoVreme();
}

void upisiNaKarticu() {
  rVreme++;

  root = SD.open(filename, FILE_WRITE);
  if (!root) {
    Serial.println("Greska prilikom upisivanja");
    return;
  }

  root.seek(0);
  root.print(rVreme);
  root.flush();

  Serial.println("Uspesno upisivanje");
  root.close();
}

void procitajFajl() {
  root = SD.open(filename);
  if (!root) {
    Serial.println("Greska prilikom otvaranja fajla");
    return;
  }

  while (root.available())
    Serial.write(root.read());

  root.close();
  Serial.println(" minuta uradjeno!");
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

unsigned long radnoVreme() {
  unsigned long count = 0;

  root = SD.open(filename);
  if (!root || !root.available()) {
    Serial.println("Timer ne radi");
    return 0;
  }

  while (root.available()) {
    char c = root.read();
    if (c < '0' || c > '9') {
      Serial.println("Pogresan format vremena");
      root.close();
      return 0;
    }

    count *= 10;
    count += c - '0';
  }

  Serial.print("Radno vreme: ");
  Serial.print(count);
  Serial.println(" minuta");

  root.close();
  return count;
}
