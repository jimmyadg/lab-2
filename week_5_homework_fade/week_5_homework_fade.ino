const int mainLed = 11;
void setup() {
  pinMode(mainLed,OUTPUT);
}

void loop()
{
   int x = 1;
   for (int i = 0; i > -1; i = i + x){
      analogWrite(mainLed, i);
      if (i == 255) x = -1;             // switch direction at peak
      delay(8);  
   } 
}
