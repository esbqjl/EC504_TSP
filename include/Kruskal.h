#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>

using namespace std;
#ifndef KRUSKAL_H
#define KRUSKAL_H
#define edge pair<int, int>

class Graph {
public:

    vector <pair<double, edge> > G;  // graph

    map<int, queue<int> > adjList; // a basic node to nodes graph
    map<int, int> edgeNum;
    vector <pair<double, edge> >
    T;  // mst
    int *parent;
    int V;  // number of vertices/nodes in graph
public:
    Graph(int V);

    void AddWeightedEdge(int u, int v, double w);

    int find_set(int i);

    void union_set(int u, int v);

    void kruskal();

    void print();

};

#endif