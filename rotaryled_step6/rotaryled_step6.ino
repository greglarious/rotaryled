#include <Encoder.h>

const int ENCODER_PIN_1 = 2;
const int ENCODER_PIN_2 = 3;
const int ENCODER_BUTTON = 4;
const int MAX_POSITION = 30;

Encoder myEncoder(ENCODER_PIN_1, ENCODER_PIN_2);
long previousLEDPosition = 0;
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
  
  long rawPosition = myEncoder.read() / 2;

  // location of an LED on the strip
  long LEDposition = rawPosition % MAX_POSITION;
  if (LEDposition < 0) LEDposition += MAX_POSITION;
  
  if (LEDposition != previousLEDPosition) {
    Serial.print("LED position is:");
    Serial.println(LEDposition);
    previousLEDPosition = LEDposition;
  }


  delay(200);
}
