void sixth() {
  int drop = random(20, 150);
  int fade = random(150, 255);
  int brightness = random(100, 200);
  float accel = 10000000;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(0, fade, brightness);
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j].nscale8(drop);
    }
    FastLED.show();
    accel = sqrt(accel); //acceleration
    delay(accel);
    //Serial.println(accel);
  }
  
}

