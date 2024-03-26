#ifndef Dijkstras_h;
#define Dijkstras_h;

#include "Arduino.h";


class Dijkstras {
    public:
      /*Graph should always be the same so can make this a local variable, we pass in the start position and end position in order to be
      * able to calculate the path from any node to any node. For example start node 0 to corner 7, corner 7 will then become the startPos.
      */
      Dijkstras(int V); // Constructor
      void shortestPath(int startPos, int endPath);
      void addEdge(int u, int v, int w);
      int findPath(int startPos, int endPos);
    private:
      int V; // Number of vertices in the graph
};

#endif
