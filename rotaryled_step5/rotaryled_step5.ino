#include <Encoder.h>

const int ENCODER_PIN_1 = 2;
const int ENCODER_PIN_2 = 3;
const int ENCODER_BUTTON = 4;

Encoder myEncoder(ENCODER_PIN_1, ENCODER_PIN_2);
long previousPosition = 0;
int  previousButton = 1;

void setup() {
  Serial.begin(9600);
  pinMode(ENCODER_BUTTON, INPUT);
  digitalWrite(ENCODER_BUTTON, HIGH); //turn pullup resistor on
}

void loop() {
  int button = digitalRead(ENCODER_BUTTON);
  if (button != previousButton) {
    if (button == 0) {
      Serial.println("button pushed");
    } else {
      Serial.println("button released");
    }
    previousButton = button;
  }
  
  long position = myEncoder.read();
  if (position != previousPosition) {
    Serial.print("position is:");
    Serial.println(position);
    previousPosition = position;
  }
  delay(200);
}
