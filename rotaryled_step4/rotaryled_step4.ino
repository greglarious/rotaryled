#include <Adafruit_NeoPixel.h>

const int NUM_LEDS = 30;           // number of leds in strip
const int LED_PIN = 5;             // pin for led strip

const int INCREMENT = 255 / NUM_LEDS;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void fadeInColor(int redMult, int greenMult, int blueMult, int speed) {
  for (int i = 0; i < NUM_LEDS; i++) {
    int redValue = i * redMult;
    int greenValue = i * greenMult;
    int blueValue = i * blueMult;
    strip.setPixelColor(i, Adafruit_NeoPixel::Color(redValue, greenValue, blueValue));
    strip.show();
    delay(speed);
  }
}

void loop() {
  // set to red
  fadeInColor(INCREMENT, 0, 0, 100);
  delay(500);

  // set to green
  fadeInColor(0, INCREMENT, 0, 100);
  delay(500);

  // set to blue
  fadeInColor(0, 0, INCREMENT, 100);
  delay(500);
}
