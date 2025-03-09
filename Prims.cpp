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

    //write code to get the mst answer
    int prims(int src){
        priority_queue<pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>> pq;
        vector<bool> mst_set (V,false);
        mst_set[src] = true;
        int ans = 0;
        pq.push({0,src});   
        while(!pq.empty()){
            auto best = pq.top();
            pq.pop();
            int to = best.second;
            int weight = best.first;
            if(mst_set[to]){
                continue;
            }
            ans += weight;
            mst_set[to] = true;
            for(auto x : l[to]){
                if(!mst_set[x.first]){
                    pq.push({x.second,x.first});
                }
            }
        }
    }  
};