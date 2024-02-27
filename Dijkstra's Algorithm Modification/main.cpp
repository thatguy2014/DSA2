//
//  main.cpp
//  DijkstraCode
//
//  Created by Stephany Coffman-Wolph on 2/14/24.
//

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;


//node structure for the linked list class
struct LLnode
{
    int weight;
    string name;
    struct LLnode *next;
};
// linked list class for the adjacency list
class linked_list {

private:
    LLnode *head,*tail;
    int count = 0;
public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }

    void add_node(int weight, string name)
    {
        count++;
        LLnode *tmp = new LLnode;
        tmp->weight = weight;
        tmp->name = name;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }

    int get_count() {
        return count;
    }

    LLnode* get_head() {
        return head;
    }
};

//will print out the given linked list in proper format
void printlinkedlist(linked_list City) {
    LLnode* tmp = City.get_head();
    for (int i = 0; i < City.get_count(); i++) {
        cout << "| " << tmp->weight << " | " << tmp->name << " |" << " -> " << '\t';
        tmp = tmp->next;
    }
    cout << "null";
    cout << endl;
    delete tmp;
}

// Structure to represent a vertex and its distance from the source vertex
struct Node {
    int vertex;                                                                             //number of the vertex
    int distance;                                                                           //distance to source vertex
    Node(int v, int d) : vertex(v), distance(d) {}                                          //makes a new node
};

// Comparison function for priority queue
struct CompareDistance {
    bool operator()(const Node& a, const Node& b) {                                         //returns true if node b is closer to source
        return a.distance > b.distance;
    }
};

// Dijkstra's algorithm to find shortest path from source to destination
//takes in a 2d array of vectors, the first value in the graph, the value of the source, and the value of the destination
vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int source, int destination) {
    int V = (int)graph.size();
    vector<int> dist(V, INT_MAX);                                                           // Initialize a vector of distances
    vector<int> prev(V, -1);                                                                // Previous vertex in shortest path
    priority_queue<Node, vector<Node>, CompareDistance> pq;                                 // initializes a priority queue of Nodes
    
    dist[source] = 0;                                                                       
    pq.push(Node(source, 0));                                                               //adds a Node to the stack (the source node)

    while (!pq.empty()) {                                                                   //runs while theres a value in pq
        int u = pq.top().vertex;                                                            //int u that is the vertex of the top node in pq
        pq.pop();                                                                           //gets rid of the top node in pq

        for (auto& neighbor : graph[u]) {                                                   //
            int v = neighbor.first;
            int weight = neighbor.second;

            // Relaxation
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push(Node(v, dist[v]));
            }
        }
    }

    // Construct shortest path
    vector<int> path;
    for (int v = destination; v != -1; v = prev[v])
        path.push_back(v);
    
    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<pair<int, int>>> graph(V);                                //adds the amount of vertices as the limit to the graph priority queue

    cout << "Enter the edges (source, destination, weight):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        //graph[v].push_back({u, w}); // For undirected graph
    }

    int source, destination;
    cout << "Enter source and destination vertices: ";
    cin >> source >> destination;

    vector<int> shortestPath = dijkstra(graph, source, destination);

    cout << "Shortest path from " << source << " to " << destination << " is: ";
    for (int vertex : shortestPath)
        cout << vertex << " ";
    cout << endl;

    return 0;
}
