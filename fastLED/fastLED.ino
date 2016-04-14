#include "FastLED.h"
#define NUM_LEDS 15
#define DATA_PIN 8
#define CLOCK_PIN 9
#define BUTTON_PIN 2
CRGB leds[NUM_LEDS];
int val;
int counter;
int caseState;
unsigned long pTime;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  LEDS.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(60);
  Serial.begin(9600);
}

void loop() {
  long cTime = millis();
  val = digitalRead(BUTTON_PIN);
  if (val == HIGH) {
    if (cTime - pTime >= 1000) {
      caseState++;
      pTime = cTime;
    }
  }
  switch (caseState) {
    case 0:
      first();
      break;

    case 1:
      second();
      break;

    case 2:
      third();
      break;

    case 3:
      forth();
      break;

    case 4:
      fifth();
      break;

    case 5:
      sixth();
      break;

    case 6:
      seventh();
      break;

    case 7:
      caseState = 0;
      break;
  }
  Serial.print("Button= ");
  Serial.print(val);
  Serial.print("  Animation= ");
  Serial.print(caseState+1);
  Serial.println();
}


