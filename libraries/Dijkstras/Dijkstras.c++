/*
Class for retrieving the shortest path from one node to another node in the maze using dijkstras algorithm
*/

#include "Arduino.h"
#include "Dijkstras.h"

typedef pair<int, int> iPair;

class Graph {
    int V; //Number of vertices in the graph
    list< pair<int, int> > *adj; //Pointer to an array containing adjacency lists

public:
    Graph(int V); //Constructor
    void addEdge(int u, int v, int w); //Function to add an edge to the graph
    void shortestPath(int startPos, int endPos); //Function to find the shortest path from source s to all other vertices
}

Graph::Graph(int V) { 
    this->V = V; // Assign number of vertices
    adj = new list<iPair> [V]; // Create an array of adjacency lists. Size of array will be V
}

void Graph::addEdge(int u, int v, int w){
    adj[u].push_back(make_pair(v,w)); // Add a new edge to the adjacency list of u. The edge is from u to v and has weight w which is 1 but idk
    adj[v].push_back(make_pair(u,w)); 
}

void Graph::shortestPath(int startPos, int endPos){
    priority_queue<iPair, vector<iPair>, greater<iPair> > // Create a priority queue to store vertices that are being preprocessed.
        pq;
    vector<int> dist(V, INF); // Create a vector for distances and initialize all distances as infinite (INF)
    vector<int> prev(V, -1); // Create a vector for previous nodes and initialize all previous nodes as -1. This is for the path
    pq.push(make_pair(0, startPos)); // Insert source itself in priority queue and initialize its distance as 0.
    dist[startPos] = 0; // Distance to the source is 0 e.g. distance from start to start is 0.

    while (!pq_empty()) { // iterate over the priority queue
        int u = pq.top().second; // The first vertex in pair is the minimum distance vertex, extract it from priority queue.
        pq.pop(); // Remove the vertex from the priority queue

        if (u == endPos){
            break; // If the destination node has been reached, break out of the loop
        }
        list<pair<int, int> >::iterator i; // Get all adjacent of u
        for (i = adj[u].begin(); i != adj[u].end(); ++i) { // Iterate through all adjacent vertices of u

            int v = (*i).first; // Get vertex label and weight of current adjacent of u.
            int weight = (*i).second; // Get weight of current adjacent of u.
 
            // If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight) {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                prev[v] = u; // Update the previous node
                pq.push(make_pair(dist[v], v)); // Add the vertex to the priority queue
            }
        }
    }
    printf("Shortest path from %d to %d: ", startPos, endPos);
    int current = endPos;
    stack<int> path;
    while (current != -1) { // While the current node is not the start node
        path.push(current); // Push the current node onto the stack
        current = prev[current]; // Move to the previous node
    }
    while (!path.empty()) { // Print the path
        printf("%d ", path.top()); // Print the top of the stack
        path.pop(); // Pop the top of the stack
    }
    printf("\n");

}

int Dijkstras(int startPos, int endPos) {
    int V = 8; // 8 corners so 8 vertices
    Graph g(V); // Create a graph with the vertices
    // Add edges to the graph based on the diagram drawn
    g.addEdge(0, 1, 1);
    g.addEdge(0, 3, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(2, 7, 1);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 5, 1);
    g.addEdge(5, 6, 1);
    g.addEdge(6, 7, 1);

    g.shortestPath(startPos, endPos) // Find the shortest path from the start node to the end node
    return 0;
}

