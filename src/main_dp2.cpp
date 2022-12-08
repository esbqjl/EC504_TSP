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


bool DEBUG_FLAG = false;

typedef struct Node {
    int id;
    double x;
    double y;

} Node;


//reference: https://github.com/qwzybug/tsp/blob/master/tsp.cc

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


int main(int argc, char *argv[]) {
    string full_file_path(argv[1]);
    string file_name = full_file_path.substr(full_file_path.find_last_of("/") + 1, full_file_path.back());

    //cout << "file name: " << file_name << endl;

    string country_id = file_name.substr(0, 2);
    int NUM_CITIES = std::stoi(file_name.substr(2, file_name.find(".")));

    //cout << "Country ID: " << country_id << ", Number of cities = " << NUM_CITIES << endl;

    // Now start to read the contents of the file

    std::ifstream infile;

    infile.open(argv[1]);
    if (!infile) {
        cout << "Error opening file " << endl;
        return -1;
    }

    Node *node_list = new Node[NUM_CITIES];
    string read_line;

    for (int i = 0; i < START_ROW; i++) {
        std::getline(infile, read_line);
    }

    for (int i = START_ROW; i < START_ROW + NUM_CITIES; i++) {
        std::getline(infile, read_line);

        size_t first_space = read_line.find_first_of(" ");
        size_t second_space = read_line.find_last_of(" ");

        node_list[i - START_ROW].id = std::stoi(read_line.substr(0, first_space));
        node_list[i - START_ROW].x = std::stof(read_line.substr(first_space, second_space));
        node_list[i - START_ROW].y = std::stof(read_line.substr(second_space, string::npos));

        if (DEBUG_FLAG)
            cout << "Node " << node_list[i - START_ROW].id << ", x = " << node_list[i - START_ROW].x << ", y = "
                 << node_list[i - START_ROW].y << endl;
    }

    infile.close();


    vector < vector<float> > c;
    for (int i = 0; i != NUM_CITIES; ++i) {
        vector<float> tmp;
        for (int j = 0; j != NUM_CITIES; ++j) {
            float dij_sq = (node_list[i].x - node_list[j].x) * (node_list[i].x - node_list[j].x) +
                           (node_list[i].y - node_list[j].y) * (node_list[i].y - node_list[j].y);

            tmp.push_back(dij_sq);
        }

        c.push_back(tmp);
    }


    int n = NUM_CITIES;
    //cout << "Exact exponential solution:" << endl << "Path: ";
    auto start = high_resolution_clock::now();
    vector<int> tour;
    tour = tsp(n, c);
    for (int i = 0; i < n; i++)
        cout << tour[i % n] + 1 << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
    //cout << endl;
    //cout << "Cost: ";
    float total_cost = 0;
    for (int i = 1; i <= n; ++i) {
        total_cost += sqrt(c[tour[i - 1]][tour[i % n]]);
    }

    //cout << total_cost << endl << endl;

//    delete node_list;
//    delete distance_sq_matrix;

    return 0;
}