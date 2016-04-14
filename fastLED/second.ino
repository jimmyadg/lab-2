//ref: https://github.com/FastLED/FastLED/wiki/Pixel-reference
void second() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(160, 255, 255);
    FastLED.show();
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j].nscale8(40); //fading tail 3 leds
    }
    delay(100);
  }
}
