#include "../include/Christofield.h"

Christofield::Christofield(double *distance_sq_matrix){
    n= distance_sq_matrix.length;
    V= sqrt(n);
    Graph g(V);
    for(int i=1;i<V;i++){
        if (distance_sq_matrix[i]!=0)
            g.AddWeightedEdge(i/V,i%V, distance_sq_matrix.length[i]);
    }
    g.kruskal();
    G=g.G;
    T=g.T;
    //edgeNum=g.edgeNum;
}
// void Christofield::findOdds(){
//     map<int,int>::iterator it;
//     for (it = edgeNum.begin(); it != edgeNum.end(); it++)
//     {
//         if (it->second %2 ==1){
//             odds.push_back(it->first);
//         }
//         else{
//             continue;
//         }
//     }

// }
// void Christofield::bestmatching(){
// }
Christofield::findEulerGraph(){
    int current=0;
    stack<int> parentNode;
    
    while (!adjList.empty()){
        path.push_back(current);
        if (!adjList.contains(current)){
            
            current=parentNode.top();
            current=parentNode.pop();
        }
        else{
            parentNode.push(current);
            current=adjList[current].top();
            adjList[parentNode.top()].pop();
            if (adjList[parentNode.top()].empty()){
                adjList.erase(parentNode.top())
            }
        }
    }
}
Christofield::makeHamiltonian(){
    path=set(path);
    path.push_back(path[0]);
    for (int i=0;i<path.size()-1;i++){
        result.push_back(make_pair(G[i*n+(i+1)],edge(i,i+1)))
    }
}
