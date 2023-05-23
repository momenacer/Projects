
const int ledPins[] = { 2, 3, 4, 5, 6, 7, 8 };

void setup() {

  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }           
}             

void loop() {

  const int ledTime[] = { 500, 600, 700, 800, 900, 1000, 1100 };

  for (int i = 0; i < 7; i++) {
    for (int brightness = 0; brightness <= 255; brightness++) {
      analogWrite(ledPins[i], brightness);
      delay(ledTime[i]/255);
    }

    delay(100);
  }

  for (int i = 6; i >= 0; i--) {
    for (int brightness = 255; brightness >= 0; brightness--) {
      analogWrite(ledPins[i], brightness);
      delay(ledTime[i]/255);
    }

    delay(100);
  }
}
