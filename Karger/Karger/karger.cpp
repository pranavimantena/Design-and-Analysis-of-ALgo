//
//  main.cpp
//  Karger
//
//  Created by Pranavi Manthena on 10/10/21.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <vector>

using namespace std;

int myrandom (int i) { return std::rand()%i;}

struct Edge
{
    
    int start;
    int end;

};
class Graph{
public:
    unsigned long V,E;
    Edge* edge;
   Graph(unsigned long a,unsigned long b)
    {
       V = a;
       E = b;
       edge = new Edge[E];
       
   }
};

class subset
{
public:
    int node1;
    int leng;
};

int search(subset subsets[], int i)
{
    if (subsets[i].node1 != i)
    subsets[i].node1 =
            search(subsets, subsets[i].node1);

    return subsets[i].node1;
}

void add(subset subsets[], int x, int y)
{
    int xroot = search(subsets, x);
    int yroot = search(subsets, y);
    if (subsets[xroot].leng < subsets[yroot].leng)
        subsets[xroot].node1 = yroot;
    else if (subsets[xroot].leng > subsets[yroot].leng)
        subsets[yroot].node1 = xroot;
    else
    {
        subsets[yroot].node1 = xroot;
        subsets[xroot].leng++;
    }
}

int karger(Graph* graph)
{
    int V = graph->V, E = graph->E;
    Edge *edge = graph->edge;
    std::set<int> set1;
    std::set<int> set2;
    subset *subsets = new subset[V];
    for (int i = 0; i < V; ++i)
    {
        subsets[i].node1 = i;
        subsets[i].leng = 0;
    }
    int vertices = V;

    std::vector<int> grand;
    for ( int i = 0 ; i < E; i++){
        grand.push_back(i);
    }
    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle( grand.begin(), grand.end(),myrandom);
    int index = 0;
    while (vertices > 2)
    {
        
    int i = grand[index];
    if ( set1.size()==0){
        set1.insert(edge[i].start);
        set1.insert(edge[i].end);
    }
    

    int subset1 = search(subsets, edge[i].start);
    int subset2 = search(subsets, edge[i].end);
    if (subset1 == subset2)
    {
        index++;
        continue;
    }
    else{
        if((set1.find(edge[i].start)!=set1.end()&&(set2.find(edge[i].start)!=set2.end() || set2.find(edge[i].end)!=set2.end())) || (set1.find(edge[i].end)!=set1.end()&&(set2.find(edge[i].start)!=set2.end() || set2.find(edge[i].end)!=set2.end())) ){
            index++;
            continue;
        }
            
        if(set1.find(edge[i].start)!=set1.end()||(set1.find(edge[i].end)!=set1.end()))
           {set1.insert(edge[i].start);
            set1.insert(edge[i].end);}
        else{
            set2.insert(edge[i].start);
            set2.insert(edge[i].end);
        }
        vertices--;
        index++;
        add(subsets, subset1, subset2);
    }
    
    }
    int mincut = 0;
    for (int i=0; i<E; i++)
    {
        int subset1 = search(subsets, edge[i].start);
        int subset2 = search(subsets, edge[i].end);
        if (subset1 != subset2)
        mincut++;
    }
    
    cout<<"{"<<"\t";
    for(auto x:set1)
    {
     cout<<x<<"\t";
        }
    cout<<"}";
    cout<<"\t"<<"{";
    for(auto x:set2)
    {
     cout<<"\t"<<x;
   }
    cout<<"}"<<"\t";
    return mincut;
}


   int main(){

    vector<Edge> edges = {{0,1},{0,2},{0,3},{0,4},{1,2},{1,3},{1,4},{2,3},{2,4},{3,4},{1,5},{4,6},{5,6},{5,7},{5,8},{6,7},{6,8},{7,8}};
   unsigned long E = edges.size();
    set<int> s1;
    for(int i=0; i<edges.size();i++)
    {
        s1.insert(edges[i].start);
        s1.insert(edges[i].end);
    }
     
    unsigned long V = s1.size();

    Graph* graph = new Graph(V,E);
    for (int i = 0 ; i < edges.size(); i++){
        graph->edge[i].start = edges[i].start;
        graph->edge[i].end = edges[i].end;
    }
        
  cout<<karger(graph)<<"\n";
    return 0;
}
