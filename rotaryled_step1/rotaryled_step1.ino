#include <Adafruit_NeoPixel.h>

const int NUM_LEDS = 30;           // number of leds in strip
const int LED_PIN = 7;             // pin for led strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void loop() {
  strip.setPixelColor(0, Adafruit_NeoPixel::Color(255, 0, 0));
  strip.show();
}
