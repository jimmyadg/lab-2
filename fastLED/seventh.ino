void seventh() {
  fill_solid(leds, 15, CHSV(255, 0, 0));
  int pos = random(NUM_LEDS); //set random starting point
  int range = random(NUM_LEDS - pos); //set random length
  int hue = random(50, 255); //set random color
  for (int i = 0; i < random(1, 15); i++) {
    fill_solid(leds + pos, range, CHSV(hue, 255, 255)); //light up
    FastLED.show();
    fill_solid(leds + pos, range, CHSV(255, 0, 0)); //clear color
    FastLED.show();
  }
  delay(random(10, 500)); //create lightening effect

}

