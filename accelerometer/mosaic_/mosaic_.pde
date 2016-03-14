import processing.serial.*;

Serial port;  
int[] readings = new int[3];
void setup() 
{
  size(600, 600);
  noStroke();
  port = new Serial(this, "/dev/tty.usbmodem1411", 9600);
}

void draw() {

  while (port.available() > 0) {
    byte [] inBuffer = port.readBytes();
    int limit = 10;
    port.readBytesUntil(limit, inBuffer);
    if (inBuffer != null) {
      String str = new String(inBuffer);
      String[] token = splitTokens(str, ",");
      if (token.length >= 3) {
        readings[0] = int(token[0]);
        readings[1] = int(token[1]);
        readings[2] = int(token[2]);
      }
      println(readings[0]);
      println(readings[1]);
      println(readings[2]);
    }
  }

  float posX = map(readings[0], 200, 450, 0.2, 1.5);
  float posY = map(readings[1], 200, 450, 0.3, 1.7);
  float posZ = map(readings[1], 200, 450, 0.1, 1.2);
  int S = (int)posZ*30;

for(int i = 0; i <15; i++)
  for (int j = 0; j < i; j++) {
    for (int k = 0; k < i; k++) {
      fill (random(255), random(255), random(255));
      noStroke();
      rect(width/i * j +25, height/i * k + 25, S*posX, S*posY);
    }
  }
}