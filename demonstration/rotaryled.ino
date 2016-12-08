#include <Encoder.h>
#include <Adafruit_NeoPixel.h>

const int NUM_LEDS = 30;            // number of leds in strip
const int LED_PIN = 7;             // pin for led strip
const int BRIGHTNESS = 255;        // brightness of all leds
const int WHEEL_SIZE = 256;        // how many entries in the color wheel
const boolean MOVE_LIGHT = false;  // move one light around or keep all lights on
const int ENCODER_PIN_1 = 2;
const int ENCODER_PIN_2 = 3;
const int ENCODER_BUTTON = 4;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_RGB + NEO_KHZ800);
Encoder encoder(ENCODER_PIN_1, ENCODER_PIN_2);
int mode = 0;
long lastPush = 0;
int autoPosition = 0;

void initializeToBlack() {
  for (int i =0; i < NUM_LEDS; i++) {
   strip.setPixelColor(i, 0);
  }  
}

void setup() {
  Serial.begin(9600);
  pinMode(ENCODER_BUTTON, INPUT);
  digitalWrite(ENCODER_BUTTON, HIGH); //turn pullup resistor on

  strip.begin();
  initializeToBlack();
  strip.show();   
}

long normalize(long value, long radix) {
  long rval = value % radix;
  if (rval < 0) return radix + rval;
  else return rval; 
}

void loop() {
  int button= digitalRead(ENCODER_BUTTON);
  if (button == 0) {
    if ((millis() - lastPush) > 250) {
      lastPush = millis();
      mode++;
      if (mode > 4) mode = 0;
    }
  }
  long knobValue = encoder.read() / 2;

  long ledPosition = normalize(knobValue, NUM_LEDS);
  long colorValue = normalize(knobValue * 5, WHEEL_SIZE);
  long sleepValue = abs(knobValue) % 500;
  
  switch(mode) {
  // off
  case 0: initializeToBlack();
          break;
  // knob moves led
  case 1: initializeToBlack();
          strip.setPixelColor(ledPosition, colorWheel(BRIGHTNESS, colorValue));
          break;
  // all on, knob makes rainbow
  case 2: for (int i =0; i < NUM_LEDS; i++) {
            strip.setPixelColor(i, colorWheel(BRIGHTNESS, colorValue));
          }
          break;
  // one auto moving light, knob adjusts speed
  case 3: 
          delay(sleepValue);
          initializeToBlack();
          
          strip.setPixelColor(autoPosition, colorWheel(BRIGHTNESS, autoPosition * (WHEEL_SIZE / NUM_LEDS)));
          autoPosition++;
          if (autoPosition >= NUM_LEDS) {
            autoPosition = 0;         
          }
          break;
  // slug of rainbow auto moving lights, knob adjusts speed
  case 4:
          const int SLUG_SIZE = 15;
          
          delay(sleepValue);
          initializeToBlack();
          
          for (int i = 0; i < SLUG_SIZE; i++) {
            strip.setPixelColor((i + autoPosition) % NUM_LEDS, colorWheel(BRIGHTNESS, i * (WHEEL_SIZE / SLUG_SIZE)));
          }
          
          autoPosition++;
          if (autoPosition >= NUM_LEDS) {
            autoPosition = 0;         
          }
          break;
  }
  strip.show();
}

// given a wheel position in 0-255 range
// return a rainbow color adjusted by intensity 0 to 1.0
uint32_t colorWheel(float intensity, byte wheelPos)
{
  const int WHEEL_THIRD = (WHEEL_SIZE - 1) / 3;
  
  if (intensity < 0.0 ) intensity = 0.0;
  if (intensity > 1.0) intensity = 1.0;

  // as wheelPos progresses from 0 to 255 once, colorIndex should progress from 0 to 255 3 times
  // find out position in current third of wheel then multiple by 3 to get full color value
  byte colorIndex = (wheelPos % WHEEL_THIRD) * 3;
  
  int fadeColor = (255 - colorIndex) * intensity;  // color going down
  int increaseColor = colorIndex * intensity;    // color going up
  
  switch (wheelPos / WHEEL_THIRD) {
    case 0:    // first third of the wheel, red fading, no green, blue increasing
      return Adafruit_NeoPixel::Color(fadeColor, 0, increaseColor);
      break;
    case 1:    // second third of the wheel no red, green increasing, blue fading
      return Adafruit_NeoPixel::Color(0, increaseColor, fadeColor);
      break;
  
    case 2:    // last third of the wheel, red increasing, green fading, no blue
      return Adafruit_NeoPixel::Color(increaseColor, fadeColor, 0);
      break;
  }
}
