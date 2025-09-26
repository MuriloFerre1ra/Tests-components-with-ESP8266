// Lib to communcate with sensor MPU 
#include <MPU6050_tockn.h>
// Lib to use communication e2e
#include <Wire.h>

MPU6050 mpu6050(Wire);

void setup() {
  //Set Port
  Serial.begin(11500);
  //Initialize communication e2e
  Wire.begin();
  //Initialize MPU
  mpu6050.begin();
  //Calibrates the sensor ##Important: The component must be a flat surface to calibrate
  mpu6050.calcGyroOffsets(true);

}

void loop() {
  mpu6050.update();
  Serial.print("Angle X: ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("Angle: Y: ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("Angle Z: ");
  Serial.print(mpu6050.getAngleZ());
  Serial.print("--------Done--------");
}
