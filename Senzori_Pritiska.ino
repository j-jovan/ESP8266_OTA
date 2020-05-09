#define senzorPritiska1 34 //30PSI
#define senzorPritiska2 35 //500PSI

//Senzori su razlicitih kapaciteta i daju razlicite rezultate
//Jedan senzor varira od 304 - 480, dok drugi varira od 436 do 656 na skali do 4000
//Greska senzora je oko 2% +- (160), sto stavlja ove brojke u granice normale
//Istraziti svejedno

int x;
int y;


void senzorPritiska() {
  x = analogRead(senzorPritiska1);
  y = analogRead(senzorPritiska2);
  if (((x >= 304) && (x <= 480)) && ((y >= 400) && (y <= 660))) {
    //Serial.println("Isti pritisak u obe komore");
  }
  else {
    //Serial.println("Prevelika razlika pritiska u komorama");
  }
  delay(1000);
}
