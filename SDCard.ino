#define SD_MISO 26
#define SD_SCK 14
#define SD_MOSI 27
#define SD_CS 12

// Na SD kartici se kreira fajl vreme.txt u koji se upisuje 
// koliko dugo je uredjaj radio na svakih x minuta za odokativno pracenje koriscenja uredjaja.
// Povrh toga, upisuju se i podaci sa PMS7003 senzora cestica kako bismo mogli da pratimo funkcionalnost uredjaja.

static char pmsFilename[128];
static const char* filename = "vreme.txt";
static unsigned long rVreme;

void init_SDCard() {
  DPRINT("init_SDCard() start");
  File root;
  DPRINT("Inicijalizacija SD kartice...");
  if (!SD.begin(SD_CS, SD_MOSI, SD_MISO, SD_SCK)) {
    DPRINTLN("neuspesna");
    return;
  }
  DPRINTLN("uspesna");
  root = SD.open("/");
  if (!root) {
    DPRINTLN("Greska prilikom otvaranja fajla");
    return;
  }
  if (!openPMSFile()) {
    DPRINTLN("Greska prilikom otvaranja PMS fajla");
    return;
  }
  printDirectory(root, 0);
  root.close();
  rVreme = radnoVreme();
  DPRINT("init_SDCard() end");
  DPRINT("-------------------------------");
}
bool openPMSFile() {
  DPRINT("openPMSFile() start");

  File pmsFile;
  String name;
  int i = 0;
  do {
    name = "PMS_" + String(i++) + ".txt";
    name.toCharArray(pmsFilename, 128);
  } while (SD.exists(pmsFilename));

  pmsFile = SD.open(pmsFilename, FILE_WRITE);
  if (!pmsFile) {
    DPRINTLN("Greska prilikom otvaranja PMS fajla");
    return false;
  }

  pmsFile.seek(0);
  //pmsFile.print("PMS1.0\t\tPMS2.5\t\tPMS10\n");
  pmsFile.flush();
  pmsFile.close();
  DPRINT("openPMSFile() end");
  return true;
}
void upisiPMSData(PMS::DATA& data) {
  DPRINT("upisiPMSData(PMS::DATA& data) start");

  File pmsFile;
  String line = String(data.PM_AE_UG_1_0) + "," + String(data.PM_AE_UG_2_5) + "," + String(data.PM_AE_UG_10_0) + "\n";
  pmsFile = SD.open(pmsFilename, FILE_WRITE);
  if (!pmsFile) {
    DPRINTLN("Greska prilikom upisivanja u PMS file");
    return;
  }
  pmsFile.print(line);
  pmsFile.flush();
  DPRINTLN("Uspesno upisivanje u PMS file");
  DPRINTLN("upisiPMSData(PMS::DATA& data) end");

  pmsFile.close();
}
void upisiNaKarticu() {
  File fileVreme;
  rVreme++;

  fileVreme = SD.open(filename, FILE_WRITE);
  if (!fileVreme) {
    DPRINTLN("Greska prilikom upisivanja vremena");
    return;
  }

  fileVreme.seek(0);
  fileVreme.print(rVreme);
  fileVreme.flush();

  DPRINTLN("Uspesno upisivanje vremena");
  fileVreme.close();
}
void procitajFajl() {
  File fileVreme;
  fileVreme = SD.open(filename);
  if (!fileVreme) {
    DPRINTLN("Greska prilikom otvaranja vreme.txt");
    return;
  }

  while (fileVreme.available())
    Serial.write(fileVreme.read());

  fileVreme.close();
  DPRINTLN(" minuta uradjeno!");
}
void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      DPRINT('\t');
    }
    DPRINT(entry.name());
    if (entry.isDirectory()) {
      DPRINTLN("/");
      printDirectory(entry, numTabs + 1);
    } else {
      DPRINT("\t\t");
      DPRINTLN(entry.size());
    }
    entry.close();
  }
}
unsigned long radnoVreme() {
  unsigned long count = 0;
  File fileVreme;
  fileVreme = SD.open(filename);
  if (!fileVreme || !fileVreme.available()) {
    DPRINTLN("Timer ne radi");
    return 0;
  }
  while (fileVreme.available()) {
    char c = fileVreme.read();
    if (c < '0' || c > '9') {
      DPRINTLN("Pogresan format vremena");
      fileVreme.close();
      return 0;
    }

    count *= 10;
    count += c - '0';
  }
  DPRINT("Radno vreme: ");
  DPRINT(count);
  DPRINTLN(" minuta");
  fileVreme.close();
  return count;
}
