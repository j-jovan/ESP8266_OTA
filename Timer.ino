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

/*
  void timerPMS(){
    if (seconds == 0) {
    pms.wakeUp();
    Serial.println("Budjenje");
  }
  if (seconds == 30) {
    pms.requestRead();
    //Serial.println("Zahtevaj citanje");
    if (pms.readUntil(data))  {
      Serial.print("PM 1.0 (ug/m3): ");
      Serial.println(data.PM_AE_UG_1_0);
      Serial.print("PM 2.5 (ug/m3): ");
      Serial.println(data.PM_AE_UG_2_5);
      Serial.print("PM 10.0 (ug/m3): ");
      Serial.println(data.PM_AE_UG_10_0);
      pmsSenzorDisplej();
    }
    else
      Serial.println("No data.");
  }
  pms.sleep();
  if (seconds == 60) {
    upisiNaKarticu(minutes);
  }
  delay(500);
  }
*/
