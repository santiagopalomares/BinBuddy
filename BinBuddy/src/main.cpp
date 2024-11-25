#include <Arduino.h>
#include <Servo.h>

const int BAUD_RATE = 9600;
const int SERVO_PIN = 17;
Servo platform;

void setup() {
  Serial.begin(BAUD_RATE);
  platform.attach(SERVO_PIN);
  Serial.println("starting");
}

void loop() {
  platform.write(0);
  delay(1000)
  platform.write(179);
  delay(1000);
}
