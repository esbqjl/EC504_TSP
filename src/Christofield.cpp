#include "../include/Christofield.h"

Christofield::Christofield(double *distance_sq_matrix, int N){
    n= pow(N,2);
    cout<<n<<endl;
    adjmatrix=new double[n];
    O_G= distance_sq_matrix;
    V= N;
    Graph g(V);
    for(int i=0;i<n;i++){
        if (distance_sq_matrix[i]!=0)
            g.AddWeightedEdge(i/V,i%V, distance_sq_matrix[i]);
    }
    g.kruskal();
    fill_n(adjmatrix,n,-1);
    
    for (int i=0;i<g.T.size();i++){
        adjmatrix[g.T[i].second.first*V+g.T[i].second.second]=g.T[i].first;
        adjmatrix[g.T[i].second.second*V+g.T[i].second.first]=g.T[i].first;
    }
    adjList=g.adjList;

    edgeNum=g.edgeNum;
}

// void Christofield::findEulerGraph(){
//     int current=0;
//     stack<int> parentNode;
    
//     while (!adjList.empty()){
//         paths.push_back(current);
//         cout<<current<<endl;
//         if (adjList.count(current)<1){
//             if(!parentNode.empty()){
//                 cout<<"loser: "<<current<<endl;
//                 current=parentNode.top();
//                 parentNode.pop();
//             }
//             else{
//                 current=adjList.begin()->first;
//             }
//         }
//         else{
//             parentNode.push(current);
//             current=adjList[current].top();
//             adjList[parentNode.top()].pop();
//             if (adjList[parentNode.top()].empty()){
//                 adjList.erase(parentNode.top());
//             }
//         }
//     }
// }
void Christofield::findEulerGraph(){
    bestmatching();
    int x=0;
    int y=0;
    
    int child=-1;
    map<int,queue<int>>:: iterator it;
    it= adjList.begin();
    int current=it->first;
     //second Node
    while (!adjList.empty()){
        paths.push_back(current);
        if(adjList.count(current)<1){
            it++;
            current=it->first;
        }
        else{
            child=adjList[current].front();
            adjList[current].pop();
            if (adjList[current].empty()){
                adjList.erase(current);
            }
            if(adjmatrix[current*V+child]!=-1){

                
                adjmatrix[current*V+child]=-1;
                adjmatrix[child*V+current]=-1;
                
                current=child;
            }
        }
        
    }
}
void Christofield::makeHamiltonian(){
    unordered_set <int> s(paths.begin(),paths.end());
    
    paths.assign( s.begin(), s.end() );
   
    
    paths.push_back(paths[0]);
    for (int i=0;i<paths.size()-1;i++){
        
        result.push_back(make_pair(sqrt(O_G[paths[i]*V+ paths[i+1]]),edge(paths[i]+1,paths[i+1]+1)));
        paths[i]+=1;
    }
}
void Christofield::print() {
  double total_weight=0;
  cout << "Edge :"
     << " Weight" << endl;
  for (int i = 0; i < result.size(); i++) {
    cout << result[i].second.first << " - " << result[i].second.second << " : "
       << result[i].first;
    total_weight+=(result[i].first);
    cout << endl;
  }
  cout<<"total: "<<total_weight<<endl;
  cout<<paths.size()<<endl;
}
void Christofield :: findOdds(){
    
    for (auto i : edgeNum){
        if(i.second%2==1){
            
            odds.push_back(i.first);
        }
    }
}
void Christofield:: bestmatching(){
    findOdds();
    
    
    int node_1 =-1;
    int node_2 =-1;
    for(int i=0;i<odds.size()-1;i++){
        node_1=i;
        if (odds[i]!=-1){
            double least_path=numeric_limits<double>::max();
            for (int j=i+1;j<odds.size();j++){
                if(odds[j]!=-1){
                    if (adjmatrix[odds[i]*V+odds[j]]==-1){
                        least_path=O_G[odds[i]*V+odds[j]];
                        node_2=j;
                    }
                }
            }
            edgeNum[odds[node_1]]+=1;
            edgeNum[odds[node_2]]+=1;
            cout<<"Node1 ";
            cout<<node_1<<endl;
            cout<<"Node2 ";
            cout<<node_2<<endl;
            adjmatrix[odds[node_1]*V+odds[node_2]]=least_path;
            adjmatrix[odds[node_2]*V+odds[node_1]]=least_path;
            adjList[node_1].push(node_2);
            adjList[node_2].push(node_1);
            odds[node_1]=-1;
            odds[node_2]=-1;
        }
    }
}