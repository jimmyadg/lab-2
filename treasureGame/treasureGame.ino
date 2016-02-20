#include <Servo.h>

String myName;   //Declare a String variable to hold your name
int treasureX, treasureY;
int inputX, inputY;
int nearness;
int servoAngle = 1;

// NOTE: We started the servo range at 10 instead of 1 since many servos can go into a BAD jittery
// high current state at their lowest angles.  This can damage your servo!
const int servoMin = 10;   // adjust these if your servo gets jittery!
const int servoMax = 175;  // adjust these if your servo gets jittery!

Servo myservo;

// Gets a good integer and returns it.
int readNum (char *prompt) {
  int inputNum = 0;
  while (inputNum < 1 || inputNum > 9) {
    Serial.println ("All numbers must be between 1 and 9 inclusive!");
    Serial.println(prompt);        //Prompt User for input
    while (Serial.available() == 0) {} // loop till user hits return key
    inputNum = Serial.parseInt();
    Serial.print("You entered: ");
    Serial.print(inputNum);
    Serial.print("\n\n");
  }
  return (inputNum);
}

// this is not mathematically correct but nonetheless useful for our purposes
// The returned number will get larger perportional to distance from treasure
// It can range from 0 - 16
int findNearness () {
  int nearnessX, nearnessY;

  // subtract larger X from smaller
  if (treasureX >= inputX)
    nearnessX = treasureX - inputX;
  else
    nearnessX = inputX - treasureX;

  // subtract larger Y from smaller
  if (treasureY >= inputY)
    nearnessY = treasureY - inputY;
  else
    nearnessY = inputY - treasureY;

  return (nearnessX + nearnessY);
}

void servoWiggle () {
  for (int i = 0; i < 3; i++) {
    myservo.write(70);
    delay(200);
    myservo.write(110);
    delay(200);
  }

}

// clear serial terminal
void clearTerminal () {
  for (int i = 3; i > 0; i--) { // counting backwards from 3 to 0
    Serial.print("Clearing screen in ");
    Serial.print(i);
    Serial.println(" seconds.");
    delay (1000);
  }
  for (int i = 0; i < 100; i++) { // counting backwards from 3 to 0
    Serial.println("");
  }
}

void setup() {
  Serial.begin(9600);      // turn on Serial Port MAKE SURE YOU HAVE NO LINE ENDING IN THE TERMINAL!!
  myservo.attach(9);
  myservo.write(servoMin);
  tone(11, 3000, 1500);
}

void loop() {
  int toneFreq = 2000;

  inputX = 0;
  inputY = 0;
  servoWiggle();
  Serial.println("Hello Hider.");
  treasureX = readNum("Please enter the X location to hide the treasure:");
  treasureY = readNum("Please enter the Y location to hide the treasure:");
  clearTerminal ();
  Serial.println("The treasure is hidden!\n");

  Serial.println("Seeker.  Enter your name:");
  while (Serial.available() == 0) {}          //Wait for user input
  myName = Serial.readString();               //Read user input into myName
  Serial.print("Hello ");
  Serial.print(myName);
  Serial.println(".  Good to meet you!\n");

  while (!(treasureX == inputX && treasureY == inputY)) {
    inputX = readNum("Guess the X location of the treasure:");
    inputY = readNum("Guess the Y location of the treasure:");
     if(treasureX == inputX) {
      Serial.println("X is correct!");
      myservo.write(40);
     }
     if(treasureY == inputY) {
      Serial.println("Y is correct!");
      myservo.write(15);
     }
    Serial.print("Your nearness quotient is: ");
    Serial.print(findNearness()); // NOTE: a function returning something used as argument to ANOTHER function!!
    Serial.println(",\n");
    toneFreq = map (findNearness(), 0, 16, 10000, 40);  // map our nearness range to a reverse tone range
    tone(11, toneFreq, 200);  // note the new argument... what does it do?
    delay (300);
    tone(11, toneFreq, 200);
    servoAngle = map (findNearness(), 0, 16, servoMin, servoMax - 30);  // map our nearness range to (most of) the servo range
    // saving the last 30 degrees for classwork!
    myservo.write(servoAngle);
  }

  // "you won" jingle
  tone(11, 3000, 200);
  delay (200);
  tone(11, 4500, 200);
  delay (200);
  tone(11, 9000, 200);
  delay (200);
  tone(11, 12000, 200);

  Serial.println("You Won!\n\n\nRestarting:");
  servoWiggle();

}
