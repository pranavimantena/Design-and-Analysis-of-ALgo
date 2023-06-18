
//
//  main.cpp
//  Ford
//
//  Created by Pranavi Manthena on 10/12/21.
//

#include <iostream>
#include <string.h>
#include <queue>
#include <vector>
#include <set>

using namespace std;
bool bfs(vector<vector<int>> rGraph, int s, int t, int parent[])
{
    unsigned long V = rGraph.size();
    vector<bool> visited(V);

    for(int i=0; i<V; i++)
    {
        visited[i]=false;
    }
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}

int fordFulkerson(vector<vector<int>>adj, int s, int t)
{
    int u, v;
    unsigned long n = adj.size();
    vector<vector<int>> rGraph = adj;

    int parent[n];
    int max_flow = 0;
    
    while (bfs(rGraph, s, t, parent))
    {
        vector<int> path;
        path.push_back(t);
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path.push_back(u);
            path_flow = min(path_flow, rGraph[u][v]);
        }
        cout<<" Augmenting Path: ";
        for(auto i:path)
        {cout<<i<<" ";}
        cout<<" min flow "<<path_flow<<"\n";
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            cout<<"Residual edge: "<<u<<" "<<v<<" New Value:"<<rGraph[u][v]<<"\n";
            rGraph[v][u] += path_flow;
            cout<<"Reverse Residual edge: "<<v<<" "<<u<<" New Value:"<<rGraph[v][u]<<"\n";
        }
        max_flow += path_flow;
    }
    cout<<"Max Flow is : ";
    return max_flow;
}
int main()
{
    vector<vector<int>> graph = {{0,1,16},{0,2,13},{1,2,10},{1,3,12},{2,1,4},{2,4,14},{3,2,9},{3,5,20},{4,3,7},{4,5,4}};
    set<int> s1;
    for(int i=0; i<graph.size();i++)
    {
        s1.insert(graph[i][0]);
        s1.insert(graph[i][1]);

    }
    unsigned long V = s1.size();
    
    vector<vector<int>> adj(V);
    for ( int i = 0; i < V; i++){
        for ( int j = 0 ; j < V; j++){
            adj[i].push_back(0);
        }
    }
    
    
    for ( int i = 0 ; i < graph.size(); i++){
        adj[graph[i][0]][graph[i][1]] = graph[i][2];
    }
    
    cout  << fordFulkerson(adj, 0, 5)<< "\n";
    
}
