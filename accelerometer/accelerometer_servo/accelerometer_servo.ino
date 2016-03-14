//mpu 6050 code reference http://playground.arduino.cc/Main/MPU-6050#short

#include<Wire.h>
#include <Servo.h>

const int MPU = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
unsigned long pTime = 0;
Servo servo;
void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  servo.attach(A3);
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

  int posX = map(AcX,-1000,1000,0,90);
  int posY = map(AcY,-1000,1000,90,180);
  int posZ = map(AcZ,-1000,1000,1000,200);
  Serial.print("AcX =  ");
  Serial.print(AcX);
  Serial.print(" AcY = ");
  Serial.print(AcY);
  Serial.print(" AcZ = ");
  Serial.print(AcZ);
  Serial.println();
  if(cTime - pTime >= posZ){
    if(AcX>AcY) servo.write(posX);
    else servo.write(posY);
    pTime = cTime;
  }
 
}
