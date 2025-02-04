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

    void bfshelper(int start,vector <bool> &visited) {  // O (V + E) i.e. Linear Time Complexity
        queue<int> q;
        

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

    void bfs(int total, int src){
        vector<bool> visited(total, false);
        for(int i = 0;i < 6;i++){
            if(!visited[i]){
                bfshelper(i,visited);
                cout<<endl;
            }
        }
    }

    void dfshelper(int u,vector<bool> &vis){
        vis[u] = true;
        cout<<u<<" ";

        for (auto v : l[u]){
            if(!vis[v]){
                dfshelper(v,vis);
            }
        }
    }

    void dfs(int total,int src){
        
        vector<bool> vis (7, false);
        for(int i=0;i<total-1;i++){
            if(!vis[i]){
                dfshelper(i,vis);
                cout<<endl;
            }
        }
    }
    bool cycleUndirectedHelper(int src, int par, vector<bool> &vis){
        vis[src] = true ;
        
        for(auto v : l[src]){
            if(!vis[v]){
                if(cycleUndirectedHelper(v,src,vis)){
                    return true;
                }
            }else{
                if(v == par){
                    return true;
                }
            }
        }

        return false;
    }

    bool isCycleUndirected(int total){

        vector<bool> vis (total, false);
        return cycleUndirectedHelper(0,-1,vis);

    }
};

int main() {
    Graph graph(10);  // Define the number of vertices
    
    graph.addEdge(1, 6);
    graph.addEdge(6, 4);
    graph.addEdge(4, 3);
    graph.addEdge(4, 9);
    graph.addEdge(3, 8);
    graph.addEdge(3, 7);
    graph.addEdge(0, 2);
    graph.addEdge(2, 5);

    cout<< graph.isCycleUndirected(10);
    return 0;
}
