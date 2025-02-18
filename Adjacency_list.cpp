#include <iostream>  
#include <list>    
#include<queue>
using namespace std; 

class Graph {
    int V;  
    list<int>* l; // Array of lists
    bool isUndirected;

public:
    // Constructor
    Graph(int V, bool isUndirected) {
        this->isUndirected = isUndirected;
        this->V = V;
        l = new list<int>[V]; // Allocate memory for adjacency list
    }

    // Add an edge (undirected graph)
    void addEdge(int u, int v) {
        l[u].push_back(v);
        if(isUndirected){
            l[v].push_back(u);
        }
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

//     bool cycleDirectedHelper(int src, vector<bool>&vis,vector<bool>&path){
//         vis[src]=true;
//         path[src]=true;
//         for(auto v : l[src]){
//             if(!vis[v]){
//                 if(cycleDirectedHelper(v,vis,path)){
//                     return true;
//                 }else{
//                     if(path[v]){
//                         return true;
//                     }
//                 }
//             }
//         }
//         path[src]= false;
//         return false;
//     }
//     bool isCycleDirected(){
//         vector<bool> vis (V,false);
//         vector<bool> path (V, false);
//         for(int i=0;i<V;i++){
//             if(!vis[i]){
//                 if (cycleDirectedHelper(i,vis,path))
//                 {
//                     return true;
//                 }            
//             }
//         }
//         return false;    
//     }
// };
// int main() {
//     Graph graph(4,false);  // Define the number of vertices   
//     graph.addEdge(1, 6);
//     graph.addEdge(6, 4);
//     graph.addEdge(4, 3);
//     graph.addEdge(4, 9);
//     graph.addEdge(3, 8);
//     graph.addEdge(3, 7);
//     graph.addEdge(0, 2);
//     graph.addEdge(2, 5);
//     cout<< graph.isCycleDirected();
//     return 0;
// }
    bool cycleDirectedHelper(int src, vector<bool>& vis, vector<bool>& path) {
        vis[src] = true;
        path[src] = true;

        for (auto v : l[src]) {
            if (!vis[v]) {
                if (cycleDirectedHelper(v, vis, path)) {
                    return true;
                }
            }
            else if (path[v]) {  // If vertex is visited AND in current path
                return true;
            }
        }

        path[src] = false;  // Remove from current path
        return false;
    }

    bool isCycleDirected() {
        vector<bool> vis(V, false);
        vector<bool> path(V, false);

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                if (cycleDirectedHelper(i, vis, path)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isBipartite() {
    queue<int> q;
    vector<bool> vis(V, false); // To track visited nodes
    vector<int> colour(V, -1); // To store colors: -1 (uncolored), 0, or 1

    // Start BFS from each unvisited node to handle disconnected graphs
    for (int i = 0; i < V; i++) {
        if (!vis[i]) {
            q.push(i);
            colour[i] = 0; // Start coloring the first node with 0
            vis[i] = true;

            while (!q.empty()) {
                int src = q.front();
                q.pop();

                // Process all neighbors of the current node
                for (auto v : l[src]) {
                    if (!vis[v]) {
                        colour[v] = 1 - colour[src]; // Assign opposite color
                        vis[v] = true;              // Mark as visited
                        q.push(v);                  // Add to the queue
                    } else if (colour[v] == colour[src]) {
                        // If a neighbor has the same color, it's not bipartite
                        return false;
                    }
                }
            }
        }
    }

    return true; // If no conflicts are found, the graph is bipartite
    }

void all_path_helper(int src, int dest, vector<int>& vis, vector<int>& path) {
        if (src == dest) {
            path.push_back(dest);  // Include destination in the path
            for (int node : path) cout << node << " ";
            cout << endl;
            path.pop_back();  // Remove destination for backtracking
            return;
        }

        vis[src] = 1;
        path.push_back(src);

        for (auto v : l[src]) {
            if (!vis[v]) {
                all_path_helper(v, dest, vis, path);
            }
        }

        vis[src] = 0;
        path.pop_back();  // Backtracking: Remove last node
    }

    void all_path(int src, int dest) {
        vector<int> visited(V, 0);
        vector<int> path; // Use vector<int> instead of string
        all_path_helper(src, dest, visited, path);
    }
};

int main() {
    Graph g(5 ,false);  // Define the number of vertices
    
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    cout << "All paths from 0 to 4:" << endl;
    g.all_path(0, 4);
    return 0;
}