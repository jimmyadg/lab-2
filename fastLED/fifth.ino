void fifth() {
  static uint8_t hue = 0;

  for (int i = 0; i < NUM_LEDS; i++) {
    if (counter % 2 == 0 && counter != 0) {
      hue += 10; //change color each step
    } else {
      hue == hue;
    }
    leds[i] = CHSV(hue, 255, 255);
    FastLED.show();
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j].nscale8(90); //fading tail 4 leds
    }
    delay(100);
  }
  for (int i = NUM_LEDS; i > 0; i--) {
    if (counter % 2 == 0 && counter != 0) {
      hue += 10; //change color each step
    } else {
      hue == hue;
    }
    leds[i] = CHSV(hue, 255, 255);
    FastLED.show();
    for (int j = NUM_LEDS; j > 0; j--) {
      leds[j].nscale8(90); //fading tail 4 leds
    }
    delay(100);
  }
  counter++;
}
