// Ukljucivanje / iskljucivanje UV lampi koje sterilisu komore

void ukljuciUV() {
  digitalWrite(relejUV, HIGH);
  delay(10);
}

void iskljuciUV() {
  digitalWrite(relejUV, LOW);
  delay(10);
}
