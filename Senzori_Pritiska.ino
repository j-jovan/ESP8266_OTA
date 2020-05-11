#define senzPritiskaPin1 32 //30PSI
#define senzPritiskaPin2 36 //500PSI

//Senzori su razlicitih kapaciteta i daju razlicite rezultate
//Jedan senzor varira od 304 - 480, dok drugi varira od 436 do 656 na skali do 4000
//Greska senzora je oko 2% +- (160), sto stavlja ove brojke u granice normale
//Istraziti svejedno

int senzPritiska1;
int senzPritiska2;


int senzorPritiska1() {
  senzPritiska1 = analogRead(senzPritiskaPin1);
  //  if (((x >= 304) && (x <= 480)) && ((y >= 400) && (y <= 660))) {
  //    //Serial.println("Isti pritisak u obe komore");
  //  }
  //  else {
  //    //Serial.println("Prevelika razlika pritiska u komorama");
  //  }
  return senzPritiska1;

}
int senzorPritiska() {
  senzPritiska1 = analogRead(senzPritiskaPin2);
  //  if (((x >= 304) && (x <= 480)) && ((y >= 400) && (y <= 660))) {
  //    //Serial.println("Isti pritisak u obe komore");
  //  }
  //  else {
  //    //Serial.println("Prevelika razlika pritiska u komorama");
  //  }
  return senzPritiska1;

}
