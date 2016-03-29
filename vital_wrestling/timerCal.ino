//transfer fan analog read data into LED fadelevel
void timerCal() {
  long cTime = millis();

  if (cTime - timer1 >= interval) { //debouncing
    if (val1 != 0) {
      diff1 = (int)(val1 / 10); //measure how hard player one blows
      fadeLevel1 += diff1; //apply addup
    }

    timer1 = cTime; //reseting timer1
  }

  if (cTime - timer2 >= interval) { //debouncing
    if (val2 != 0) {
      diff2 = (int)(val2 / 10); //measure how hard player two blows
      fadeLevel2 += diff2; //apply addup
    }

    timer2 = cTime; //reseting timer2
  }
}
