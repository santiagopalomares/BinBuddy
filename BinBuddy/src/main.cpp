#include <Arduino.h>
#include <Servo.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

const int BAUD_RATE = 9600;
const int SERVO_PIN = 17;

// WiFi credentials
const char* SSID = "iPhone";
const char* PASSWORD = "01tiago10";

// Server details
const char* serverURL = "http://44.203.141.233:5000/recyclable";

Servo platform;

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

String fetchDecision() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Reconnecting...");
    connectToWiFi();
  }

  HTTPClient http;
  http.begin(serverURL);
  int httpResponseCode = http.GET();

  String response = "UNDETERMINED";
  if (httpResponseCode > 0) {
    response = http.getString();
    Serial.println("TTT: " + response);
  } else {
    Serial.printf("HTTP GET failed with error: %s\n", http.errorToString(httpResponseCode).c_str());
  }
  http.end();
  Serial.printf("response value", response);
  return response;
}

void tiltPlatform(String decision) {
  if (decision == "true") {
    Serial.println("Decision: YES -> Tilt Left");
    platform.write(40); // Tilt left
    delay(5000);        // Hold position for 5 seconds
  } else if (decision == "false") {
    Serial.println("Decision: NO -> Tilt Right");
    platform.write(170); // Tilt right
    delay(5000);         // Hold position for 5 seconds
  } else {
    Serial.println("Decision: UNDETERMINED -> Center");
    platform.write(105); // Center position
    delay(5000);         // Hold position for 5 seconds
  }

  // Return to center after action
  Serial.println("Returning to center position.");
  platform.write(105);
  delay(1000);
}

void setup() {
  Serial.begin(BAUD_RATE);
  platform.attach(SERVO_PIN);

  connectToWiFi();
  Serial.println("Servo control ready.");
  Serial.println("Press 'g' to fetch decision and tilt platform.");
}

void loop() {
  // Check for keypress
  if (Serial.available() > 0) {
    char key = Serial.read(); // Read the incoming character
    if (key == 'g' || key == 'G') { // Check if it's 'g' (case-insensitive)
      Serial.println("Key 'g' pressed. Fetching decision...");
      
      // Fetch decision from the server
      String decision = fetchDecision();

      // Act based on the server's response
      tiltPlatform(decision);
    } else {
      Serial.printf("Key '%c' pressed. No action.\n", key);
    }
  }
}
