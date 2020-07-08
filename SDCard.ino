#define SD_MISO 26
#define SD_SCK 14
#define SD_MOSI 27
#define SD_CS 12

static char pmsFilename[128];
static const char* filename = "vreme.txt";
static unsigned long rVreme;

void init_SDCard() {
  File root;
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

  if (!openPMSFile()) {
    Serial.println("Greska prilikom otvaranja PMS fajla");
    return;
  }

  printDirectory(root, 0);
  root.close();

  rVreme = radnoVreme();
}


bool openPMSFile()
{
  File pmsFile;
  String name;
  int i = 0;

  do {
    name = "/session_" + String(i++) + ".txt";
    name.toCharArray(pmsFilename, 128);
  } while(SD.exists(pmsFilename));

  pmsFile = SD.open(pmsFilename, FILE_WRITE);
  if (!pmsFile) {
    Serial.println("Greska prilikom otvaranja PMS fajla");
    return false;
  }

  pmsFile.seek(0);
  pmsFile.print("PMS1.0\t\tPMS2.5\t\tPMS10\n");
  pmsFile.flush();
  pmsFile.close();

  return true;
}

void upisiPMSData(PMS::DATA& data) 
{
  File pmsFile;
  String line = String(data.PM_AE_UG_1_0) + "\t\t" + String(data.PM_AE_UG_2_5) + "\t\t" + String(data.PM_AE_UG_10_0) + "\n";
  
  pmsFile = SD.open(pmsFilename, FILE_WRITE);
  if (!pmsFile) {
    Serial.println("Greska prilikom upisivanja u PMS file");
    return;
  }

  pmsFile.print(line);
  pmsFile.flush();

  Serial.println("Uspesno upisivanje");
  pmsFile.close();
}

void upisiNaKarticu() {
  File fileVreme;
  rVreme++;

  fileVreme = SD.open(filename, FILE_WRITE);
  if (!fileVreme) {
    Serial.println("Greska prilikom upisivanja");
    return;
  }

  fileVreme.seek(0);
  fileVreme.print(rVreme);
  fileVreme.flush();

  Serial.println("Uspesno upisivanje");
  fileVreme.close();
}

void procitajFajl() {
  File fileVreme;
  fileVreme = SD.open(filename);
  if (!fileVreme) {
    Serial.println("Greska prilikom otvaranja fajla");
    return;
  }

  while (fileVreme.available())
    Serial.write(fileVreme.read());

  fileVreme.close();
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
  File fileVreme;

  fileVreme = SD.open(filename);
  if (!fileVreme || !fileVreme.available()) {
    Serial.println("Timer ne radi");
    return 0;
  }

  while (fileVreme.available()) {
    char c = fileVreme.read();
    if (c < '0' || c > '9') {
      Serial.println("Pogresan format vremena");
      fileVreme.close();
      return 0;
    }

    count *= 10;
    count += c - '0';
  }

  Serial.print("Radno vreme: ");
  Serial.print(count);
  Serial.println(" minuta");

  fileVreme.close();
  return count;
}
