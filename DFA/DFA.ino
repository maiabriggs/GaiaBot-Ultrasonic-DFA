#include <HCSR04.h>
#include <FiveSensors.h>
#include <Movements.h>
#include <RoboClaw.h>
#include <Dijkstras.h>
#include <ArduinoSTL.h>


Dijkstras dijkstras(8); // 0 is the start position, 7 is the end position

void setup() {
 Serial.begin(9600);
}

void loop() {
  int shortestPathLength = dijkstras.findPath(0, 7);

  // Print the length of the shortest path
  Serial.print("Length of shortest path from 0 to 7: ");
  Serial.println(shortestPathLength);
}
