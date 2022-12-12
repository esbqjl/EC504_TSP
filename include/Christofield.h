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
#include <queue>
using namespace std;
#ifndef CHRISTOFIELD_H
#define CHRISTOFIELD_H
#define edge pair<int, int>

class Christofield {
    public:
        vector <int> paths;
        vector<pair<double, edge>> result;
        map<int,int> edgeNum;
        //map<int, stack<int>> adjList; 
        map<int,queue<int>>adjList;
        double* adjmatrix;
        vector<int> odds;
    
        int n;
        int V;
        double* O_G;
        Christofield(double *distance_sq_matrix,int N);
        void remove(vector<int> &v);
        void findOdds();
        void bestmatching();
        void print();
        void findEulerGraph();
        void makeHamiltonian();
};

#endif