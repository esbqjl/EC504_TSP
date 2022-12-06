#include "KruskalDouble.h"
#include <bits/stdc++.h>
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
#include <set>
using namespace std;
#ifndef CHRISTOFIELDDOUBLE_H
#define CHRISTOFIELDDOUBLE_H
#define edge pair<int, int>

class Christofield {
    public:
        vector <int> paths;
        vector<pair<double, edge>> G;
        vector<pair<double, edge>> T;
        vector<pair<double, edge>> result;
        //map<int,int> edgeNum;
        map<int, stack<int>> adjList; //first int is parent node, second int is child node, third node is weight
    
    
        int n;
        int V;
        double* O_G;
        Christofield(double *distance_sq_matrix,int N);
        
        //void findOdds();
        //void bestmatching();
        void print();
        void findEulerGraph();
        void makeHamiltonian();
};

#endif