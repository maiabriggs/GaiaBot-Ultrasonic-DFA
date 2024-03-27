#include "Dijkstras.h"

// Define the number of vertices in the graph
#define NUM_VERTICES 7

void setup() {
    Serial.begin(9600);

    // Initialize Dijkstras object
    Dijkstras dijkstras(NUM_VERTICES);

    // Add edges to the graph (example graph)
    dijkstras.addEdge(0, 1, 1);
    dijkstras.addEdge(1, 0, 1);
    dijkstras.addEdge(1, 2, 1);
    dijkstras.addEdge(2, 1, 1);
    dijkstras.addEdge(2, 3, 1);
    dijkstras.addEdge(3, 2, 1);
    dijkstras.addEdge(2, 0, 1);
    dijkstras.addEdge(1, 6, 1);
    dijkstras.addEdge(6, 1, 1);
    dijkstras.addEdge(3, 4, 1);
    dijkstras.addEdge(4, 3, 1);
    dijkstras.addEdge(4, 5, 1);
    dijkstras.addEdge(4, 5, 1);
    dijkstras.addEdge(5, 6, 1);
    dijkstras.addEdge(6, 5, 1);

    // Calculate the shortest path
    dijkstras.shortestPath(0, 6);

    // Get the shortest path array
    int* shortestPath = dijkstras.getShortestPathList(0, 6);

    // Print the shortest path array
    Serial.println("Shortest path:");
    int pathLenght = dijkstras.getPathLength(0,6) + 1;
    for (int i = 0; i < pathLenght; ++i) {
        // Check if the current vertex in the shortest path array is valid
        if (shortestPath[i] != -1) {
            Serial.print(shortestPath[i]);
            if (i < pathLenght - 1 && shortestPath[i + 1] != -1) {
                Serial.print(" -> ");
            }
        }
    }
    Serial.println();
    Serial.print(dijkstras.getPathLength(0, 6));

    // Free memory allocated for the shortest path array
    delete[] shortestPath;
}


void loop() {
    // Nothing to do in the loop for this test
}