#include "../include/Kruskal.h"

bool sortbynode(const pair<int, edge > &a, const pair<int, edge > &b) {
    return (a.second.first < b.second.first);
}

Graph::Graph(int V) {
    parent = new int[V];

    //i 0 1 2 3 4 5
    //parent[i] 0 1 2 3 4 5
    for (int i = 0; i < V; i++)
        parent[i] = i;

    G.clear();
    T.clear();
}

void Graph::AddWeightedEdge(int u, int v, double w) {
    G.push_back(make_pair(w, edge(u, v)));
}

int Graph::find_set(int i) {
    // If i is the parent of itself
    if (i == parent[i])
        return i;
    else
        // Else if i is not the parent of itself
        // Then i is not the representative of his set,
        // so we recursively call Find on its parent


        return find_set(parent[i]);
}

void Graph::union_set(int u, int v) {
    parent[u] = parent[v];
}

void Graph::kruskal() {
    int i, uRep, vRep;
    sort(G.begin(), G.end());  // increasing weight

    for (i = 0; i < G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            T.push_back(G[i]);  // add to tree
            adjList[G[i].second.first].push(G[i].second.second);
            adjList[G[i].second.second].push(G[i].second.first);
            edgeNum[G[i].second.first] += 1;
            edgeNum[G[i].second.second] += 1;
            union_set(uRep, vRep);
        }
    }

}

void Graph::print() {
    cout << "Edge :"
         << " Weight" << endl;
    for (int i = 0; i < T.size(); i++) {
        cout << T[i].second.first << " - " << T[i].second.second << " : "
             << T[i].first;
        cout << endl;
    }
}
