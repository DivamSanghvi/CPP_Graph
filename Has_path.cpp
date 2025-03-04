#include <iostream>  
#include <list>    
#include<queue>
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

    void bfs(int start) {  // O (V + E) i.e. Linear Time Complexity
        queue<int> q;
        vector<bool> visited(V, false);

        q.push(start);
        visited[start] = true;

        cout << "BFS Traversal: ";

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            // Visit all unvisited neighbors
            for (int neighbor : l[u]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        cout << endl;
    }

    void dfs(int u,vector<bool> &vis){
        vis[u] = true;
        cout<<u<<" ";

        for (auto v : l[u]){
            if(!vis[v]){
                dfs(v,vis);
            }
        }
    }

    bool hasPathHelper(int src,int dest,vector<bool> &visited){
        if(src==dest){
            return true;
        }
        visited[src]=true;
        for(auto i : l[src]){
            if(!visited[i]){
                if(hasPathHelper(i,dest,visited)){
                    return true;
                };
            }

        }
        return false;
    }

    bool hasPath(int u, int v){
        vector<bool> visited (7, false);
        return hasPathHelper(u,v,visited);
    }
};

int main() {
    Graph graph(7);  // Define the number of vertices
    
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);
    graph.addEdge(5, 6);

    cout<<graph.hasPath(2,8);
    
    return 0;
}
