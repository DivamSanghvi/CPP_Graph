#include <iostream>  
#include <list>    

using namespace std; 

class Graph {
    int V;  
    list<pair<int,int>>* l; // Array of lists

public:
    // Constructor
    Graph(int V) {
        this->V = V;
        l = new list<pair<int,int>>[V]; // Allocate memory for adjacency list
    }

    // Add an edge (undirected graph)
    void addEdge(int u, int v,int w) {
        l[u].push_back(make_pair(v,w));
        l[v].push_back(make_pair(u,w));
    }

    // Print adjacency list
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << " -> ";
            for (auto neighbor : l[i]) {
                cout << "(" << neighbor.first << ", weight: " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph graph(5);  // Define the number of vertices

    graph.addEdge(0, 1, 5);
    
    graph.addEdge(1, 2 ,1);
    graph.addEdge(1, 3,3);
    
    graph.addEdge(2, 3,1);
    graph.addEdge(2, 4,2);

    cout << "Graph adjacency list:\n";
    graph.printGraph();

    return 0;
}
