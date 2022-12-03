#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
#ifndef KRUSKAL_H
#define KRUSKAL_H
#define edge pair<int, int>

class Graph {
  private:
      vector<pair<int, edge>> G;  // graph
      map<int, stack<int>> adjList; // a basic node to node graph
      //map<int,int> edgeNum;
      vector<pair<int, edge> > T;  // mst
      int *parent;
      int V;  // number of vertices/nodes in graph
      public:
      Graph(int V);
      void AddWeightedEdge(int u, int v, int w);
      int find_set(int i);
      void union_set(int u, int v);
      void kruskal();
      void print();
      
};
#endif