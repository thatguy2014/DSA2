#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <list>

using namespace std;

// Structure to represent a vertex and its distance from the source vertex
struct Node {
    int vertex;       // Number of the vertex
    int distance;     // Distance to source vertex

    Node(int v, int d) : vertex(v), distance(d) {}  // Constructor
};

// Linked list node for adjacency list
struct LLnode {
    int vertex;       // Vertex number
    int weight;       // Weight of the edge
    LLnode* next;     // Pointer to next node in the list

    LLnode(int v, int w) : vertex(v), weight(w), next(nullptr) {}  // Constructor
};

// Function to add an edge to the adjacency list                    
void addEdge(vector<LLnode>& adjList, int u, int v, int weight) {   //adds an edge to the linked list
    adjList[u].next = new LLnode(v, weight);                        
}                                                                   

// Dijkstra's algorithm to find shortest path from source to destination
vector<int> dijkstra(vector<LLnode>& adjList, int V, int source, int destination) {
    vector<int> dist(V, INT_MAX);  // Initialize vector of distances
    vector<int> prev(V, -1);       // Previous vertex in shortest path

    dist[source] = 0;               //sets the distance to the source to 0

    for (int i = 0; i < V - 1; ++i) {   //iterates through the adjacency list - 1
        for (int u = 0; u < V; ++u) {   //iterates through the adjacency list again
            LLnode* temp = &adjList[u]; //sets a temp node pointer to the value of u in adjlist
            while (temp) {                  //while temp !null
                int v = temp->vertex;       //sets the vertex to v
                int weight = temp->weight;  //sets the weight to weight

                
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) { //checks if the distance to u from v is less than or greater to the saved value
                    dist[v] = dist[u] + weight;                         //overwrites the distance to v
                    prev[v] = u;                                        //marks that u was taken to get there
                }

                temp = temp->next;          //iterates temp
            }
        }
    }

    // Construct shortest path
    vector<int> path;                                                   //creates a vector for the shortest path
    for (int v = destination; v != -1; v = prev[v])                     //honestly idk how this iterates but it works
        path.push_back(v);                                              //adds to path the reverse order of the best way to get there

    reverse(path.begin(), path.end());                                  //reverses path
    return path;                                                        //outputs the answer
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    vector<LLnode> adjList(V);  // Adjacency list representation of graph

    cout << "Enter the edges (source, destination, weight):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(adjList, u, v, w);
        // addEdge(adjList, v, u, w); // For undirected graph
    }

    int source, destination;
    cout << "Enter source and destination vertices: ";
    cin >> source >> destination;

    vector<int> shortestPath = dijkstra(adjList, V, source, destination);

    cout << "Shortest path from " << source << " to " << destination << " is: ";
    for (int vertex : shortestPath)
        cout << vertex << " ";
    cout << endl;

    return 0;
}
