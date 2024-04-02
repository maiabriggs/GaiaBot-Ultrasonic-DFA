// Dijkstras.cpp

#include "PriorityQueue.h"
#include "Stack.h"
// Dijkstras.cpp

#include "Arduino.h"
#include "Dijkstras.h"
#include <limits.h>

Dijkstras::Dijkstras(int V) {
    this->V = V;
    dist = new int[V];
    prev = new int[V];
    adj = new int*[V];
    for (int i = 0; i < V; ++i) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        adj[i] = new int[V];
        for (int j = 0; j < V; ++j) {
            adj[i][j] = 0;
        }
    }
}

void Dijkstras::addEdge(int u, int v, int w) {
    adj[u][v] = w;
}

void Dijkstras::shortestPath(int startPos, int endPos) {
    dist[startPos] = 0;
    bool visited[V] = {false};

    for (int count = 0; count < V - 1; ++count) {
        int u = minDistance(dist, visited);
        visited[u] = true;
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && adj[u][v] && dist[u] != INT_MAX && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
                prev[v] = u;  // Update the previous node for vertex v
            }
        }
    }

    // Print shortest path only if it exists
    if (dist[endPos] != INT_MAX) {
        Serial.print("Length of shortest path from ");
        Serial.print(startPos);
        Serial.print(" to ");
        Serial.print(endPos);
        Serial.print(": ");
        Serial.println(dist[endPos]);

        Serial.print("Shortest path: ");
        printPath(startPos, endPos);
        Serial.println();
    } else {
        Serial.println("No valid path found.");
    }
}

int Dijkstras::minDistance(int dist[], bool visited[]) {
    int min = INT_MAX;
    int minIndex = -1;
    for (int v = 0; v < V; ++v) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void Dijkstras::printPath(int startPos, int endPos) {
    if (endPos == startPos) {
        Serial.print(startPos);
        Serial.print(" ");
    } else if (prev[endPos] == -1) {
        Serial.println("No path found.");
    } else {
        printPath(startPos, prev[endPos]);
        Serial.print(endPos);
        Serial.print(" ");
    }
}

int Dijkstras::findPath(int startPos, int endPos) {
    Dijkstras g(7);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 0, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 1, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 2, 1);
    g.addEdge(2, 0, 1);
    g.addEdge(1, 6, 1);
    g.addEdge(6, 1, 1);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 3, 1);
    g.addEdge(4, 5, 1);
    g.addEdge(4, 5, 1);
    g.addEdge(5, 6, 1);
    g.addEdge(6, 5, 1);

    g.shortestPath(startPos, endPos);
    return 0;
}

int* Dijkstras::getShortestPathList(int startPos, int endPos) {
    // Check if a valid path exists
    if (dist[endPos] == INT_MAX) {
        return nullptr; // No valid path found, return nullptr
    }

    // Create a dynamic array to store the shortest path
    int* shortestPath = new int[V];
    int currentVertex = endPos;
    int pathLength = 0;

    // Backtrack from the end position to the start position
    while (currentVertex != startPos) {
        shortestPath[pathLength++] = currentVertex;
        currentVertex = prev[currentVertex];
    }
    shortestPath[pathLength++] = startPos; // Add the start position to the path

    // Reverse the path to get it in the correct order
    for (int i = 0; i < pathLength / 2; ++i) {
        int temp = shortestPath[i];
        shortestPath[i] = shortestPath[pathLength - i - 1];
        shortestPath[pathLength - i - 1] = temp;
    }

    return shortestPath;
}

int Dijkstras::getPathLength(int startPos, int endPos) {
    // Check if a valid path exists
    if (dist[endPos] == INT_MAX) {
        return -1; // No valid path found, return -1
    }

    int pathLength = 0;
    int currentVertex = endPos;

    // Backtrack from the end position to the start position
    while (currentVertex != startPos) {
        currentVertex = prev[currentVertex];
        pathLength++;
    }

    return pathLength;
}