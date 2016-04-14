void forth() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i == 8) hue+= 60; //change color halfway
    leds[i] = CHSV(hue, 255, 255);
    FastLED.show();
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j].nscale8(80); //fading tail 3 leds
    }
    delay(100);
  }
}
