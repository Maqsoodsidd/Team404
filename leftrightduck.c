#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

// HC-06 TX -> Arduino pin 10 or RX
// HC-06 RX -> Arduino pin 11 or TX
SoftwareSerial BTSerial(10, 11);

Adafruit_MPU6050 mpu;

// Thresholds
const float duckPitchThreshold  = 30.0;
const float leftRollThreshold   = -35.0;
const float rightRollThreshold  = 35.0;
void setup() {
  Serial.begin(9600);      // For debugging - Serial Monitor
  BTSerial.begin(9600);    // HC-06 default baud rate is 9600
  while (!Serial) delay(10);  // Wait for Serial to be ready

  // MPU6050 -> AD0 -> GND-> 0x68
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    BTSerial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  // Configure sensor ranges and bandwidth
  // 2 x 9.8ms/2
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  // Max 250 degrees per second
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  // Max frequency,  to reduce noice like human body movement.
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 initialized on address 0x68 (AD0 to GND)!");
  BTSerial.println("MPU6050 initialized on address 0x68 (AD0 to GND)!");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Get accelerometer readings
  float ax = a.acceleration.x;
  float ay = a.acceleration.y;
  float az = a.acceleration.z;

  // Calculate pitch and roll (in degrees)
  float pitch = atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
  float roll  = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / PI;

  // Print sensor values for debugging
  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print("  Roll: ");
  Serial.println(roll);

  // Decision logic for head movement detection:
  if (pitch > duckPitchThreshold) {
    Serial.println("DUCK");
    BTSerial.println("DUCK");
  }
  else if (roll < leftRollThreshold) {
    Serial.println("LEFT");
    BTSerial.println("LEFT");
  }
  else if (roll > rightRollThreshold) {
    Serial.println("RIGHT");
    BTSerial.println("RIGHT");
  }
  else {
    Serial.println("NONE");
    BTSerial.println("NONE");
  }

  delay(200);  // Adjust delay for responsiveness as needed
}
