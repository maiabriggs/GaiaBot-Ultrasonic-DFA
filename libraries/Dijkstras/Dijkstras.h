#ifndef Dijkstras_h;
#define Dijkstras_h;

#include "Arduino.h";

class Dijkstras {
    public:
      /*Graph should always be the same so can make this a local variable, we pass in the start position and end position in order to be
      * able to calculate the path from any node to any node. For example start node 0 to corner 7, corner 7 will then become the startPos.
      */
      int Dijkstras();
      void shortestPath(int startPos)
      void addEdge(int u, int v, int w);

}

#endif
