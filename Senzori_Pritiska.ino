#define senzPritiskaPin1 32 //30PSI
#define senzPritiskaPin2 36 //500PSI

float senzPritiska1; // AVG 612
float senzPritiska2; // AVG 666


float senzorPritiska1() {
  senzPritiska1 = analogRead(senzPritiskaPin1);
  float voltage = (senzPritiska1*2) / 1024.0;
  float pressure_pascal = (3.0 * ((float)voltage - 0.47)) * 1000000.0;
  float pressure_bar = pressure_pascal / 10e5;
  float pressure_psi = pressure_bar * 14.5038;
  return pressure_bar;
}

float senzorPritiska2() {
  senzPritiska2 = analogRead(senzPritiskaPin2);
  float voltage = (senzPritiska2*2) / 1024.0;
  float pressure_pascal = (3.0 * ((float)voltage - 0.47)) * 1000000.0;
  float pressure_bar = pressure_pascal / 10e5;
  float pressure_psi = pressure_bar * 14.5038;
  return pressure_bar;
}
