#define DAC1 25

int snagaMotora[10] = {178, 179, 180, 181, 181, 183, 184, 185, 186, 187};

void motorDACLoop() {
  dacWrite(DAC1, 220);
}
