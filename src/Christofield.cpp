#include "../include/Christofield.h"

Christofield::Christofield(double *distance_sq_matrix, int N){
    int n= pow(N,2);
    cout<<n<<endl;
    
    O_G= distance_sq_matrix;
    V= N;
    Graph g(V);
    for(int i=0;i<n;i++){
        if (distance_sq_matrix[i]!=0)
            g.AddWeightedEdge(i/V,i%V, distance_sq_matrix[i]);
    }
    g.kruskal();
    adjList=g.adjList;
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
void Christofield::findEulerGraph(){
    int current=0;
    stack<int> parentNode;
    
    while (!adjList.empty()){
        paths.push_back(current);
        cout<<current<<endl;
        if (adjList.count(current)<1){
            if(!parentNode.empty()){
                cout<<"loser: "<<current<<endl;
                current=parentNode.top();
                parentNode.pop();
            }
            else{
                current=adjList.begin()->first;
            }
        }
        else{
            parentNode.push(current);
            current=adjList[current].top();
            adjList[parentNode.top()].pop();
            if (adjList[parentNode.top()].empty()){
                adjList.erase(parentNode.top());
            }
        }
    }
}
void Christofield::makeHamiltonian(){
    unordered_set <int> s(paths.begin(),paths.end());
    
    paths.assign( s.begin(), s.end() );
    paths.push_back(paths[0]);
    cout<<paths.size()<<endl;
    cout<<"yeah"<<endl;
    for (int i=0;i<paths.size()-1;i++){
        result.push_back(make_pair(O_G[paths[i]*V+ paths[i+1]],edge(paths[i],paths[i+1])));
    }
}
void Christofield::print() {
  double total_weight=0;
  cout << "Edge :"
     << " Weight" << endl;
  for (int i = 0; i < result.size(); i++) {
    cout << result[i].second.first << " - " << result[i].second.second << " : "
       << result[i].first;
    total_weight+=result[i].first;
    cout << endl;
  }
  cout<<"total: "<<total_weight<<endl;
}