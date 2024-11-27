#include <Arduino.h>
#include <Servo.h>

const int BAUD_RATE = 9600;
const int SERVO_PIN = 17;
Servo platform;

void setup() {
  Serial.begin(BAUD_RATE);
  platform.attach(SERVO_PIN);
  Serial.println("Servo control ready. Enter 'R' to turn right, 'L' to turn left.");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    command = toupper(command);
    if (command == 'R') {
      Serial.println("Turning right");
      platform.write(170);
    } else if (command == 'L') {
      Serial.println("Turning left");
      platform.write(40);
    } else if (command =='C'){
      Serial.println("Center");
      platform.write(105);
    } else {
      Serial.println("Invalid command. Use 'R' or 'L'.");
    }
  }
}




// #include <Arduino.h>
// #include <HttpClient.h>
// #include <WiFi.h>
// #include <inttypes.h>
// #include <stdio.h>
// #include "esp_system.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "nvs.h"
// #include "nvs_flash.h"

// // This example downloads the URL "http://arduino.cc/"
// char ssid[50];  // your network SSID (name)
// char pass[50];  // your network password (use for WPA, or use as key for WEP)

// // Name of the server we want to connect to
// const char kHostname[] = "worldtimeapi.org";

// // Path to download (this is the bit after the hostname in the URL)
// const char kPath[] = "/api/timezone/Europe/London.txt";

// // Number of milliseconds to wait without receiving any data before we give up
// const int kNetworkTimeout = 30 * 1000;

// // Number of milliseconds to wait if no data is available before trying again
// const int kNetworkDelay = 1000;

// void nvs_access() {
//   // Initialize NVS
//   esp_err_t err = nvs_flash_init();
//   if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
//     // NVS partition was truncated and needs to be erased; retry nvs_flash_init
//     ESP_ERROR_CHECK(nvs_flash_erase());
//     err = nvs_flash_init();
//   }
//   ESP_ERROR_CHECK(err);

//   // Open NVS handle
//   Serial.println("\nOpening Non-Volatile Storage (NVS) handle... ");
//   nvs_handle_t my_handle;
//   err = nvs_open("storage", NVS_READWRITE, &my_handle);
//   if (err != ESP_OK) {
//     Serial.printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
//   } else {
//     Serial.println("Done\nRetrieving SSID/PASSWD");
//     size_t ssid_len;
//     size_t pass_len;
//     err = nvs_get_str(my_handle, "ssid", ssid, &ssid_len);
//     err |= nvs_get_str(my_handle, "pass", pass, &pass_len);
//     switch (err) {
//       case ESP_OK:
//         Serial.println("Done");
//         break;
//       case ESP_ERR_NVS_NOT_FOUND:
//         Serial.println("The value is not initialized yet!");
//         break;
//       default:
//         Serial.printf("Error (%s) reading!\n", esp_err_to_name(err));
//     }
//   }
//   // Close NVS handle
//   nvs_close(my_handle);
// }

// void setup() {
//   Serial.begin(9600);
//   delay(1000);

//   // Retrieve SSID/PASSWD from flash before anything else
//   nvs_access();

//   // Connecting to a WiFi network
//   delay(1000);
//   Serial.println("\n\nConnecting to ");
//   Serial.println(ssid);
//   Serial.printf("SSID = %s\n", ssid);
//   Serial.printf("PASSWD = %s\n", pass);
//   WiFi.begin(ssid, pass);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print("WiFi status: ");
//     Serial.println(WiFi.status());
//     Serial.print(".");
//   }

//   Serial.println("\nWiFi connected");
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());
//   Serial.print("MAC address: ");
//   Serial.println(WiFi.macAddress());
// }

// void loop() {
//   int err = 0;
//   WiFiClient c;
//   HttpClient http(c);

//   // Prepare a simple query string for testing
//   String processedValue = "example_data";
//   String queryString = "/?var=" + processedValue;

//   // Send the HTTP GET request
//   err = http.get("34.212.148.76", 5000, queryString.c_str(), NULL);
//   if (err == 0) {
//     Serial.println("startedRequest ok");
//     err = http.responseStatusCode();

//     if (err >= 0) {
//       Serial.print("Got status code: ");
//       Serial.println(err);

//       // Check response code is 200 or similar
//       err = http.skipResponseHeaders();
//       if (err >= 0) {
//         int bodyLen = http.contentLength();
//         Serial.print("Content length is: ");
//         Serial.println(bodyLen);
//         Serial.println("\nBody returned follows:");

//         unsigned long timeoutStart = millis();
//         char c;
//         // Print the response body
//         while ((http.connected() || http.available()) &&
//                ((millis() - timeoutStart) < kNetworkTimeout)) {
//           if (http.available()) {
//             c = http.read();
//             Serial.print(c);
//             bodyLen--;

//             // Reset the timeout counter as data is read
//             timeoutStart = millis();
//           } else {
//             // Pause to allow data to arrive
//             delay(kNetworkDelay);
//           }
//         }
//       } else {
//         Serial.print("Failed to skip response headers: ");
//         Serial.println(err);
//       }
//     } else {
//       Serial.print("Getting response failed: ");
//       Serial.println(err);
//     }
//   } else {
//     Serial.print("Connect failed: ");
//     Serial.println(err);
//   }
//   http.stop();

//   delay(1000);
// }
