void logic() {
  photoVal1 = analogRead(A4);
  photoVal2 = analogRead(A5);
  switch (caseState) {
    case 0:
      //      buttonVal = 0;
      //      buttonVal = digitalRead(Button);
      //      if (val1 < 80 && val2 < 80 && abs(val1 - val2) <= 2) {
      //        if (limit < 1) { //limit the serial print to print one
      //          Serial.println("Press the button to start!");
      //        }
      //

      digitalWrite(Blue, HIGH);
      if (limit < 1) { //limit the serial print to print one
        Serial.println("Press the sensors to start!");
        lcd.clear();
        lcd.print("Press the sensor");
        lcd.setCursor(0, 1);
        lcd.print("to start!");
      }

      limit = 1; //stop the if statement above

      if (photoVal1 <= 100 && photoVal2 <= 100) caseState++; //move to next case

      break;

    case 1:
      beginDis();
      caseState++;
      break;

    case 2:
      //buttonVal = 0;
      limit = 0;
      interval = 100;

      //measureWin(fadeLevel1, fadeLevel2);

      timerCal();

      analogWrite(LED1, fadeLevel1);
      analogWrite(LED2, fadeLevel2);


      if (fadeLevel1 >= 255) {
        fadeLevel1 = 255;
        winner = 1;
        caseState++;
      }

      if (fadeLevel2 >= 255) {
        fadeLevel1 = 255;
        winner = 2;
        caseState++;
      }

      Serial.print("Fan 1 =  ");
      Serial.print(val1);
      Serial.print("\t");
      Serial.print("Fan 2 =  ");
      Serial.print(val2);
      Serial.print("\t");
      Serial.print("1 =  ");
      Serial.print(fadeLevel1);
      Serial.print("\t");
      Serial.print("2 =  ");
      Serial.print(fadeLevel2);
      Serial.println();
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("P2");
      lcd.setCursor(12, 0);
      lcd.print("P1");
      lcd.setCursor(2, 1);
      lcd.print(fadeLevel2);
      lcd.setCursor(12, 1);
      lcd.print(fadeLevel1);

      break;

    case 3:
      if (winner == 1) {
        
        analogWrite(LED1, 255);
        Serial.println("Player one wins!");
        lcd.clear();
        lcd.print("Player one");
        lcd.setCursor(0, 1);
        lcd.print("wins!");
        winTone();

      } else {

        analogWrite(LED2, 255);

        Serial.println("Player two wins");
        lcd.clear();
        lcd.print("Player two");
        lcd.setCursor(0, 1);
        lcd.print("wins!");
        winTone();

      }

      delay(8000);
      setTone(2000);
      caseState++;
      break;

    case 4:
      if (limit < 1) {
        Serial.println("Press the sensors to restart");
        lcd.clear();
        lcd.print("Press the sensor");
        lcd.setCursor(0, 1);
        lcd.print("to restart!");
      }
      limit = 1;

      if (photoVal1 <= 100 && photoVal2 <= 100) reset();
      break;
  }

}




/*Used to have a servo for measuring who is winning so far, but it was
  conflicting with the fans so I took it out
*/

//void measureWin(int x , int y) {
//
//  if (x > y) {
//    if (x - y <= 90) servo.write((90 + (x - y) / 9));
//    else servo.write(180);
//
//  } else if (x < y) {
//    if (y - x <= 90) servo.write((90 - (y - x) / 9));
//    else servo.write(0);
//
//  } else servo.write(90);
//}


