#define DAC1 25
#define FADE_STEP 1

void motorDACLoop() {
  static int brightness = 0;
  static int fadeAmount = FADE_STEP;

  dacWrite(DAC1, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 200) {
    fadeAmount = -fadeAmount;
  }

}
