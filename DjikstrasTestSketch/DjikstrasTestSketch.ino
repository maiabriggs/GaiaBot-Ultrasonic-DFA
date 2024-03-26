#include <Dijkstras.h>

Dijkstras dijkstras(8); // 0 is the start position, 7 is the end position

void setup() {
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int shortestPathLength = dijkstras.findPath(, 4);

  // Print the length of the shortest path
  Serial.print("Length of shortest path from 0 to 7: ");
  Serial.println(shortestPathLength);
}
