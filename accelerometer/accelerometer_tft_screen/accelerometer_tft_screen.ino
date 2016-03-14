//mpu 6050 code reference http://playground.arduino.cc/Main/MPU-6050#short

#include<Wire.h>
#include "SPI.h"
#include "TFT_22_ILI9225.h"
#include <TFT.h>

#define TFT_RST 8
#define TFT_RS  9
#define TFT_CS  10  // SS
#define TFT_SDI 11  // MOSI
#define TFT_CLK 13  // SCK
#define TFT_LED A0

const int MPU = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
unsigned long pTime;
int interval = 800;

TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  tft.begin();
  tft.setOrientation(2); // set vertical display
  Serial.begin(9600);
}

void loop() {
  long cTime = millis();
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  Serial.print("AcX =  ");
  Serial.print(AcX);
  Serial.print(" AcY = ");
  Serial.print(AcY);
  Serial.print(" AcZ = ");
  Serial.print(AcZ);
  Serial.println();

  int x = map(AcX, -15000, 5000, 0 , 50);
  int y = map(AcY, -15000, 5000, 0, 50);
  int z = map(AcZ, -1500, 5000, 0, 50);

  if (cTime - pTime >= interval) {
    tft.clear();
    tft.setBackgroundColor(COLOR_BLACK);
    int Size;
    int rgb;
    if(AcX > AcZ){
      Size = x;
      rgb = COLOR_GREEN;
      if(AcZ > AcY){
        Size = z;
        rgb = COLOR_RED;
        if(AcY > AcX) {
          Size = y;
          rgb = COLOR_BLUE;
        }
      }
    }
    
    tft.fillCircle(80,100,Size,rgb);

    pTime = cTime;
  }

}
