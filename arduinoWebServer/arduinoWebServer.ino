#include "Robot.h"
#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "MaiaPhone";    // Your network SSID (name)
char pass[] = "DaZz1e123EmMeTt"; // Your network password
int status = WL_IDLE_STATUS;        // WiFi connection status

WiFiServer server(80);  // Create a server on port 80

// Pin configuration for the robot's sensors
const int f_trigPin = 2;
const int f_echoPin = 3;
const int m2_trigPin = 4;
const int m2_echoPin = 5;
const int m1_trigPin = 6;
const int m1_echoPin = 7;
const int fm1_trigPin = 8;
const int fm1_echoPin = 9;
const int fm2_trigPin = 10;
const int fm2_echoPin = 11;

// Create an instance of the Robot class
Robot myRobot(f_trigPin, f_echoPin, m2_trigPin, m2_echoPin, m1_trigPin, m1_echoPin, fm1_trigPin, fm1_echoPin, fm2_trigPin, fm2_echoPin);

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Wait for Serial Monitor to open

  // Attempt to connect to Wi-Fi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000); // Try to connect every 10 seconds
  }

  // If connected, print the local IP address
  Serial.println("Connected to Wi-Fi");
  printWiFiStatus();

  // Start the server
  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");
    // Wait for the client to send a request
    while (client.connected()) {
      // Read the request
      if (client.available()) {
        // Read the first line of the request
        String request = client.readStringUntil('\r');
        Serial.println(request);

        // Parse the request to extract the command parameters
        // Example: "GET /navigate?start=0&end=1 HTTP/1.1"
        if (request.indexOf("/navigate") != -1) {
          int startNodeIndex = request.indexOf("start=") + 6;
          int endNodeIndex = request.indexOf("&end=");
          int endPos = request.indexOf("HTTP") - 1;
          int startVal = request.substring(startNodeIndex, endNodeIndex).toInt();
          int endVal = request.substring(endNodeIndex + 5, endPos).toInt();
          
          // Process the command (send it to the robot)
          myRobot.navigate(startVal, endVal);

          // Respond to the client
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html><body><h1>Command received</h1></body></html>");
          break;
        }
      }
    }
    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}

void printWiFiStatus() {
  // Print the local IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
