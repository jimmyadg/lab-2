//custom set tone code for my laziness
void setTone(int x) {
  return (tone(8, x, 10));
}


//isolate "begin serial print" for easy edit
void beginDis() {
  Serial.println("Ready!");
  setTone(3000);
  delay(1500);
  Serial.println(3);
  setTone(4000);
  delay(1000);
  Serial.println(2);
  setTone(4000);
  delay(1000);
  Serial.println(1);
  setTone(4000);
  delay(1000);
  setTone(2000);
  Serial.println("GO!");
}


//isolate win tone for easy edit
void winTone() {
  tone(8, 1000, 800);
  delay(100);
  tone(8, 3500, 1000);
}
