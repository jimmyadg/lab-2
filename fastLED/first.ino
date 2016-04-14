//One pixel moving down the strip
//ref: fastLED - Cylon

void first() {
  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(160, 255, 255); //seeting color to red
      // Show the leds   
      FastLED.show();
      // go Back to Black
      leds[i] = CRGB::Black;
      delay(100);
    }
}
