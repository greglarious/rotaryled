#include <Encoder.h>

const int ENCODER_PIN_1 = 2;
const int ENCODER_PIN_2 = 3;
const int ENCODER_BUTTON = 4;

Encoder encoder(ENCODER_PIN_1, ENCODER_PIN_2);
long previousKnobValue = 0;
int  previousButton = 1;

void setup() {
  Serial.begin(9600);
  pinMode(ENCODER_BUTTON, INPUT);
  digitalWrite(ENCODER_BUTTON, HIGH); //turn pullup resistor on
}

void loop() {
  int button = digitalRead(ENCODER_BUTTON);
  if (button != previousButton) {
    previousButton = button;
    if (button == 0) {
      Serial.println("button pushed");
    } else {
      Serial.println("button released");
    }
  }
  
  long knobValue = encoder.read();
  if (knobValue != previousKnobValue) {
    previousKnobValue = knobValue;
    Serial.print("knob value is:");
    Serial.println(knobValue);
  }
  delay(200);
}
