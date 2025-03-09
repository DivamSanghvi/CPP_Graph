#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Edge {
public:
    int v;
    int wt;
    Edge(int v, int wt) {
        this->v = v;
        this->wt = wt;
    }
};

int dijkstra(int src, vector<vector<Edge>>& Graph, int V, int dest) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-Heap
    vector<int> dist(V, INT_MAX); 

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int current_node = pq.top().second;
        pq.pop();  // ✅ Pop the processed node

        if (current_node == dest) {
            return dist[current_node];  // ✅ Return as soon as we reach dest
        }

        for (auto& edge : Graph[current_node]) {
            int next_node = edge.v;
            int edge_weight = edge.wt;

            if (dist[next_node] > current_dist + edge_weight) {
                dist[next_node] = current_dist + edge_weight;
                pq.push({dist[next_node], next_node});
            }
        }
    }

    return -1; // ✅ If destination is unreachable
}

void bellmanFord(vector<vector<Edge>> graph, int V, int src, int dest){
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for(int i = 0; i < V-1; i++){
        for(int u = 0; u < V; u++){
            for(auto& edge : graph[u]){
                int v = edge.v;
                int wt = edge.wt;

                if(dist[u] != INT_MAX && dist[u] + wt < dist[v]){
                    dist[v] = dist[u] + wt;
                }
            }
        }
    }

    for(int u = 0; u < V; u++){
        for(auto& edge : graph[u]){
            int v = edge.v;
            int wt = edge.wt;

            if(dist[u] != INT_MAX && dist[u] + wt < dist[v]){
                cout << "Negative cycle detected" << endl;
                return;
            }
        }
    }

    cout << "Shortest path from " << src << " to " << dest << " is: " << dist[dest] << endl;
}

int main() {
    int V = 6;
    vector<vector<Edge>> Graph(V);

    Graph[0].push_back(Edge(1, -1));
    Graph[0].push_back(Edge(2, 4));
    Graph[1].push_back(Edge(2, 1));
    Graph[1].push_back(Edge(3, 7));
    Graph[2].push_back(Edge(4, 3));
    Graph[3].push_back(Edge(5, 1));
    Graph[4].push_back(Edge(3, 2));
    Graph[4].push_back(Edge(2, 5));

    int src = 0, dest = 5;
    //int shortest_path = dijkstra(src, Graph, V, dest);
    bellmanFord(Graph, V, src, dest);
    // if (shortest_path == -1)
    //     cout << "No path exists from " << src << " to " << dest << endl;
    // else
    //     cout << "Shortest path from " << src << " to " << dest << " is: " << shortest_path << endl;

    // return 0;
}
