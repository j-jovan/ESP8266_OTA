void timer(unsigned int& seconds, unsigned int& minutes) {
  unsigned long timeNow = 0;

  timeNow = millis() / 1000;
  seconds = timeNow % 60;
  minutes = timeNow / 60;

  DPRINT("Vreme je: ");
  DPRINT(minutes);
  DPRINT(" minuta i ");
  DPRINT(seconds);
  DPRINTLN(" sekundi");
}
