void third() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(160, 255, 255);
    FastLED.show();
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j].nscale8(90); //fading tail 4 leds
    }
    delay(100);
  }
  for (int i = NUM_LEDS; i > 0; i--) {
    leds[i] = CHSV(160, 255, 255);
    FastLED.show();
    for (int j = NUM_LEDS; j > 0; j--) {
      leds[j].nscale8(90); //fading tail 4 leds
    }
    delay(100);
  }
}
