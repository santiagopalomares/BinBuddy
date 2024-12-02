#include <Arduino.h>
#include <Servo.h>

const int BAUD_RATE = 9600;
const int SERVO_PIN = 17;

// pins used to create a two-bit data bus
const int SIG_PIN_ONE = 37; // Bit 0
const int SIG_PIN_TWO = 38; // Bit 1

Servo platform;

void setup() {
  Serial.begin(BAUD_RATE);
  platform.attach(SERVO_PIN);
  
  // Set the signal pins as input
  pinMode(SIG_PIN_ONE, INPUT);
  pinMode(SIG_PIN_TWO, INPUT);
  
  Serial.println("Servo control ready.");
  Serial.println("00 -> Center");
  Serial.println("10 -> Tilt Left");
  Serial.println("01 -> Tilt Right");
}

void loop() {
  // Read the two-bit signal
  int bit0 = digitalRead(SIG_PIN_ONE); // Read the first bit
  int bit1 = digitalRead(SIG_PIN_TWO); // Read the second bit

  // Combine bits to form a 2-bit value
  int signal = (bit1 << 1) | bit0;

  // Control servo based on signal
  switch (signal) {
    case 0b00: // Center
      Serial.println("Signal: 00 -> Center");
      platform.write(105); // Center position
      break;
    case 0b01: // Tilt Right
      Serial.println("Signal: 01 -> Tilt Right");
      platform.write(170); // Tilt right position
      break;
    case 0b10: // Tilt Left
      Serial.println("Signal: 10 -> Tilt Left");
      platform.write(40); // Tilt left position
      break;
    case 0b11: // Invalid signal
      Serial.println("Signal: 11 -> Invalid, no action");
      break;
    default:
      Serial.println("Unexpected signal value.");
      break;
  }

  delay(100);
}
