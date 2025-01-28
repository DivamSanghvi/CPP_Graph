#include <iostream>  
#include <list>    

using namespace std; 

class Graph {
    int V;  
    list<int>* l; // Array of lists

public:
    // Constructor
    Graph(int V) {
        this->V = V;
        l = new list<int>[V]; // Allocate memory for adjacency list
    }

    // Add an edge (undirected graph)
    void addEdge(int u, int v) {
        l[u].push_back(v);
        l[v].push_back(u);
    }

    // Print adjacency list
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << " -> ";
            for (int neighbor : l[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph graph(5);  // Define the number of vertices

    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    cout << "Graph adjacency list:\n";
    graph.printGraph();

    return 0;
}
