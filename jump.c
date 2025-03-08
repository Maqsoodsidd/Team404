#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

// Define HC-06 connection pins: (RX, TX)
// Connect HC-06 TX -> Arduino pin 10 (RX) and HC-06 RX -> Arduino pin 11 (TX)
SoftwareSerial BTSerial(10, 11);

Adafruit_MPU6050 mpu;

// Threshold for jump detection on the Y-axis (in m/s^2)
// When the sensor is oriented with an extra 90° rotation, the Y-axis captures the jump drop.
const float jumpAccelThreshold = 5.0;

void setup() {
  Serial.begin(9600);      // For debugging via Serial Monitor
  BTSerial.begin(9600);    // HC-06 default baud rate is 9600
  while (!Serial) delay(10);  // Wait for Serial to be ready

  // Initialize the MPU6050 sensor (with AD0 tied to GND, default address 0x68)
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    BTSerial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  // Configure sensor ranges and bandwidth (optional tuning)
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("MPU6050 (Leg Sensor) initialized on address 0x68 (AD0 to GND)!");
  BTSerial.println("MPU6050 (Leg Sensor) initialized on address 0x68 (AD0 to GND)!");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // With the sensor rotated 90° more, the jump's acceleration change is most visible on the Y-axis.
  float ay = a.acceleration.y;

  Serial.print("Acceleration (Y): ");
  Serial.println(ay);

  // If the Y-axis acceleration falls below the threshold, detect a jump.
  if (ay < jumpAccelThreshold) {
    Serial.println("JUMP");
    BTSerial.println("JUMP");
  } else {
    Serial.println("NONE");
    BTSerial.println("NONE");
  }

  delay(200);  // Adjust delay for responsiveness as needed
}
