#include<iostream>
#include<vector>
#include<queue>
#include<climits>

using namespace std;

class Graph{
    int V;
    vector<pair<int,int>> *l;
    bool isUndirected;

public:
    Graph(int V,bool isUndirected){
        this->V = V;
        this->isUndirected = isUndirected;
        l = new vector<pair<int,int>>[V];
    }

    void addEdge(int u,int v,int wt){
        l[u].push_back({v,wt});
        if(isUndirected){
            l[v].push_back({u,wt});
        }
    }

    void printGraph(){
        for(int i=0;i<V;i++){
            cout<<i<<"->";
            for(auto v : l[i]){
                cout<<"("<<v.first<<","<<v.second<<")";
            }
            cout<<endl;
        }
    }

    void prims(int src){
        vector<int> parent(V,-1);
        vector<int> dist(V,INT_MAX);
        vector<bool> mst(V,false);

        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

        pq.push({0,src});
        dist[src] = 0;

        while(!pq.empty()){
            int u = pq.top().second;
            pq.pop();

            mst[u] = true;

            for(auto v : l[u]){
                int node = v.first;
                int wt = v.second;

                if(!mst[node] && dist[node] > wt){
                    dist[node] = wt;
                    parent[node] = u;
                    pq.push({wt,node});
                }
            }
        }

        for(int i=0;i<V;i++){
            cout<<parent[i]<<"-"<<i<<" "<<dist[i]<<endl;
        }
    }
    
};