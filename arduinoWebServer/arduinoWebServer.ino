#include "Robot.h"
#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "MaiaPhone";    // Your network SSID (name)
char pass[] = "DaZz1e123EmMeTt"; // Your network password
int status = WL_IDLE_STATUS;        // WiFi connection status

WiFiServer server(80);  // Create a server on port 80

// Pin configuration for the robot's sensors
int fTrig = 7;
int fEcho = 6;

int m2Trig = 9;
int m2Echo = 8;

int m1Trig = 3;
int m1Echo = 2;

int fm2Trig = 10;
int fm2Echo = 11;

int fm1Trig = 5;
int fm1Echo = 4;

// Create an instance of the Robot class
Robot myRobot(fTrig, fEcho, m2Trig, m2Echo, m1Trig, m1Echo, fm1Trig, fm1Echo, fm2Trig, fm2Echo);

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
