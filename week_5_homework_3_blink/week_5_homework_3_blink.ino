const int mainLed = 11;
const int metronome = 10;
int caseState;
int counter = 6; //two zeros per fade so 3*2 = 6

void setup() {
  pinMode(mainLed, OUTPUT);
  pinMode(metronome, OUTPUT);
}

void loop()
{
  int x = 1;
  switch (caseState) {
    case 0:
      for (int i = 0; i > -1; i = i + x) {
        analogWrite(mainLed, i);
        if (i == 255) x = -1;             // switch direction at peak
        if (i == 0){
          counter --;
          if(counter == 0) caseState = 1;
        }
        delay(8); 
      }
      break;
    case 1:
      digitalWrite(11, HIGH);
      delay(1000);
      digitalWrite(11, LOW);
      delay(1000);
      digitalWrite(11, HIGH);
      delay(1000);
      digitalWrite(11, LOW);
      delay(1000);
      counter = 6;
      caseState = 0;
      
      break;
  }
}
