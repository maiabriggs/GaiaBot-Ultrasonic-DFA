// Dijkstras.h

#ifndef Dijkstras_h
#define Dijkstras_h

#include "Arduino.h"

class Dijkstras {
public:
    Dijkstras(int V);
    void addEdge(int u, int v, int w);
    void shortestPath(int startPos, int endPos);
    int findPath(int startPos, int endPos);
    int V;
    int* prev;
    int* getShortestPathList(int startPos, int endPos);
    int getPathLength(int startPos, int endPos);

private:
    int** adj;
    int* dist;
    

    int minDistance(int dist[], bool visited[]);
    void printPath(int startPos, int endPos);
};

#endif
