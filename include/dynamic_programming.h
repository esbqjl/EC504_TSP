#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <cfloat>
#include <stack>
#include <vector>

#include <chrono>
using namespace std::chrono;

#define START_ROW 7
using namespace std;

#ifndef EC504_TSP_DYNAMIC_PROGRAMMING_H
#define EC504_TSP_DYNAMIC_PROGRAMMING_H



vector<int> tsp(int n, vector < vector<float> > &cost);

void dp(vector < vector<float> > c, int NUM_CITIES);

vector<int> tsp(int n, vector < vector<float> > &cost) {
    long nsub = 1 << n;
    vector < vector<float> > opt(nsub, vector<float>(n));

    for (long s = 1; s < nsub; s += 2)
        for (int i = 1; i < n; ++i) {
            vector<int> subset;
            for (int u = 0; u < n; ++u)
                if (s & (1 << u))
                    subset.push_back(u);

            if (subset.size() == 2)
                opt[s][i] = cost[0][i];

            else if (subset.size() > 2) {
                float min_subpath = FLT_MAX;
                long t = s & ~(1 << i);
                for (vector<int>::iterator j = subset.begin(); j != subset.end(); ++j)
                    if (*j != i && opt[t][*j] + cost[*j][i] < min_subpath)
                        min_subpath = opt[t][*j] + cost[*j][i];
                opt[s][i] = min_subpath;
            }
        }

    vector<int> tour;
    tour.push_back(0);

    bool selected[n];
    fill(selected, selected + n, false);
    selected[0] = true;

    long s = nsub - 1;

    for (int i = 0; i < n - 1; ++i) {
        int j = tour.back();
        float min_subpath = FLT_MAX;
        int best_k;
        for (int k = 0; k < n; ++k)
            if (!selected[k] && opt[s][k] + cost[k][j] < min_subpath) {
                min_subpath = opt[s][k] + cost[k][j];
                best_k = k;
            }
        tour.push_back(best_k);
        selected[best_k] = true;
        s -= 1 << best_k;
    }
    tour.push_back(0);

    return tour;
}

void dp(vector < vector<float> > c, int NUM_CITIES) {

    int n = NUM_CITIES;
    cout << endl << "Exact dynamic programming solution :" << endl << "Path: "<<endl;
    auto start = high_resolution_clock::now();
    vector<int> tour;
    tour = tsp(n, c);

    ofstream dp_result;
    dp_result.open ("dp_result.tsp");
    for (int i = 0; i < n; i++)
        dp_result << tour[i % n] + 1 << endl;
    dp_result.close();

    for (int i = 0; i <= n; i++)
        cout << tour[i % n] + 1 << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken : "<< duration.count() << " microseconds" << endl;
    cout << endl;
    cout << "Cost: "<<endl;
    float total_cost = 0;
    for (int i = 1; i <= n; ++i) {
        total_cost += sqrt(c[tour[i - 1]][tour[i % n]]);
    }
    cout<<total_cost<<endl;

}


#endif //EC504_TSP_DYNAMIC_PROGRAMMING_H
