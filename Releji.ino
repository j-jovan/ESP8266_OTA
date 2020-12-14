// Ukljucivanje / iskljucivanje UV lampi koje sterilisu komore

void ukljuciUV() {
  digitalWrite(relejUV, HIGH);
  DPRINTLN("Relej UV HIGH");
  delay(10);
}

void iskljuciUV() {
  digitalWrite(relejUV, LOW);
  DPRINTLN("Relej UV LOW");
  delay(10);
}
