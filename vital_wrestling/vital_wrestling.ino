//#include <Servo.h>

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define LED1 10
#define LED2 6
#define Blue 13
#define FAN1 A0
#define FAN2 A1
#define Button 2

//Servo servo;


int caseState, val1, val2, buttonVal, photoVal1, photoVal2, fadeLevel1, fadeLevel2, interval, winner, pos, limit, diff1, diff2;

unsigned long timer1, timer2;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Blue, OUTPUT);
  pinMode(Button, INPUT);
  //servo.attach(5);
  analogWrite(FAN1, 0);
  analogWrite(FAN2, 0);
  lcd.begin(16,2);
  Serial.begin(9600);

}

void loop() {

  val1 = analogRead(FAN1); //analog read fan1
  val2 = analogRead(FAN2); //analog read fan2
  logic();
  debug();

}
