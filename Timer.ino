unsigned long timeNow = 0;
unsigned long timeLast = 0;

int startingHour = 0;

int seconds = 0;
int minutes = 0;

int timer() {
  timeNow = millis() / 1000;
  seconds = timeNow - timeLast;

  if (seconds == 60) {
    timeLast = timeNow;
    minutes = minutes + 1;
  }

  Serial.print("Vreme je: ");
  Serial.print(minutes);
  Serial.print(" minuta i ");
  Serial.print(seconds);
  Serial.println(" sekundi");

  return seconds;
}
