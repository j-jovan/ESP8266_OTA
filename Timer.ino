void timer(int& seconds, int& minutes) {
  unsigned long timeNow = 0;

  timeNow = millis() / 1000;
  seconds = timeNow % 60;
  minutes = timeNow / 60;

  Serial.print("Vreme je: ");
  Serial.print(minutes);
  Serial.print(" minuta i ");
  Serial.print(seconds);
  Serial.println(" sekundi");
}
