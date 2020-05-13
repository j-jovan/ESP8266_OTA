#define senzPritiskaPin1 32 //30PSI
#define senzPritiskaPin2 36 //500PSI

float senzPritiska1; // AVG 612
float senzPritiska2; // AVG 666


float senzorPritiska1() {
  senzPritiska1 = analogRead(senzPritiskaPin1);
  float srednjaVrednost1 = senzPritiska1 / 612;
  return srednjaVrednost1;

}
float senzorPritiska2() {
  senzPritiska2 = analogRead(senzPritiskaPin2);
  float srednjaVrednost2 = senzPritiska2 / 666;
  return srednjaVrednost2;
}
