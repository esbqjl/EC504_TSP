#include "Kruskal.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <stdio.h>
#include <vector>
#include <limits>
using namespace std;
#ifndef CHRISTOFIELD_H
#define CHRISTOFIELD_H
#define edge pair<int, int>
class Christofield {
    private:
        vector <int> paths;
        vector<pair<int, edge>> G;
        vector<pair<int, edge>> T;
        vector<pair<int, edge>> result;
        //map<int,int> edgeNum;
        map<int, stack<int>> adjList; //first int is parent node, second int is child node, third node is weight
    protected:
    public:
        int n;
        int V;
        
        Christofield(double *distance_sq_matrix);
        ~Christofield();
        //void findOdds();
        //void bestmatching();
        
        void findEulerGraph();
        void makeHamiltonian();
}

#endif