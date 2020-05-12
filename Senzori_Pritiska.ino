#define senzPritiskaPin1 32 //30PSI
#define senzPritiskaPin2 36 //500PSI

int senzPritiska1; // AVG 612
int senzPritiska2; // AVG 666


int senzorPritiska1() {
  senzPritiska1 = analogRead(senzPritiskaPin1);
  return senzPritiska1;

}
int senzorPritiska2() {
  senzPritiska1 = analogRead(senzPritiskaPin2);
  return senzPritiska1;
}
