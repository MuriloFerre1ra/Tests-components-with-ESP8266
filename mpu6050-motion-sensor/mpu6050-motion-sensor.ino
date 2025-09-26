// Lib to use communication e2e
#include <Wire.h>
// Lib to communcate with sensor MPU 
#include <MPU6050_tockn.h>

MPU6050 mpu6050(Wire);

void setup() {
  //Set Port ##115200 is better to ESP8266 debbuger
  Serial.begin(115200);
  //Initialize communication I2E
  Wire.begin(D2,D1); //Ports SDA AND SCL
  //Initialize MPU
  mpu6050.begin();
  //Calibrates the sensor ##Important: The component must be a flat surface to calibrate
  mpu6050.calcGyroOffsets(true);

}

void loop() {
  mpu6050.update();

  Serial.print("1 - Angle X: ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("    2 - Angle: Y: ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("    3 - Angle Z: ");
  Serial.print(mpu6050.getAngleZ());

  Serial.println();//Break line

  delay(500);
}
