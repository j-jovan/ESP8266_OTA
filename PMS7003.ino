#define RXD2 39
#define TXD2 34

// Citajuci neku dokumentaciju senzora dosli smo (neko je dosao) do podatka 
// da mu odgovara da proverava podatke na svakih 10-15 minuta.

HardwareSerial SerialPMS(1);
PMS pms(SerialPMS);

void PMS7003_Setup() {
  SerialPMS.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pms.passiveMode();
}

void PMS7003WakeUp() {
  pms.wakeUp();
  DPRINTLN("PMS Wake Up");
}

void PMS7003Sleep() {
  pms.sleep();
  DPRINTLN("PMS Sleep");
}

void PMS7003ReadData(PMS::DATA& data) {
  pms.requestRead();
  if (pms.readUntil(data))
  {
    DPRINT("PM 1.0 (ug/m3): ");
    DPRINTLN(data.PM_AE_UG_1_0);
    DPRINT("PM 2.5 (ug/m3): ");
    DPRINTLN(data.PM_AE_UG_2_5);
    DPRINT("PM 10.0 (ug/m3): ");
    DPRINTLN(data.PM_AE_UG_10_0);
    //delay(20);
  } else {
    DPRINTLN("PMS ne vraca podatke");
  }
}
