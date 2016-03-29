////photocell button (lags the progam so I took it out)
//void trigger(int first, int second, int state) {
//  photoVal1 = analogRead(first);
//  photoVal2 = analogRead(second);
//  
//  if (state == 1) {
//    if (photoVal1 <= 100 && photoVal2 <= 100) caseState++;
//  } else {
//    if (photoVal1 <= 100 && photoVal2 <= 100) reset();
//  }
//}


//reset the game
void reset() {
  fadeLevel1 = 0;
  fadeLevel2 = 0;
  limit = 0;
  //servo.write(90);
  analogWrite(LED1, fadeLevel1);
  analogWrite(LED2, fadeLevel2);
  caseState = 0;
}
