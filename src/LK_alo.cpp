//
// Created by Nelson Wang on 11/30/22.
//
#include "LK_alo.h"
#include <vector>
#include <cmath>
#include <set>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>



using namespace std;

pair<int, int> getNormalEdge(int a, int b) {
    if (a < b) {
        return make_pair(a, b);
    } else {
        return make_pair(a, b);
    }
}

LK::LK(vector<pair<double, double> > &locate, vector<int> &id) {
    this->locate = locate;
    this->id = id;
    size = id.size();
    tour = vector<int>(size, 0);
    for (int i = 0; i < size; i++) {
        tour[i] = (i + 1) % size;
    }
    edgeDistances = vector<vector<double> >(size, vector<double>(size, 0));
    double singleEdgeDistance;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            singleEdgeDistance = sqrt(pow((locate[i].first - locate[j].first), 2) +
                                      pow((locate[i].second - locate[j].second), 2));
            edgeDistances[i][j] = singleEdgeDistance;
            edgeDistances[j][i] = singleEdgeDistance;
        }
    }
}

double LK::currentTourDistance() {
    double distance;
    for (int i = 0; i < size; i++) {
        distance += edgeDistances[i][tour[i]];
    }
    return distance;
}

void LK::edgeMove(int tourstart) {
    set<pair<int, int> > broken_set, joined_set;
    vector<int> tour_opt = tour;
    double g_opt = 0;
    double g = 0; // := G_i
    double g_local; // := g_i
    int lastNextV = tourstart;
    int fromV;
    int nextV;
    int nextFromV;
    int lastPossibleNextV;
    pair<int, int> broken_edge;
    double y_opt_length;
    double broken_edge_length;
    double g_opt_local;

    fromV = tour[lastNextV];
    long initialTourDistance = currentTourDistance();

    do {
        // default, no nextV is found
        nextV = -1;


        broken_edge = getNormalEdge(lastNextV, fromV); // := x_i
        broken_edge_length = edgeDistances[broken_edge.first][broken_edge.second];



        // Condition 4(c)(1)
        if (joined_set.count(broken_edge) > 0) break;

        // y_i := (fromV, nextV)
        for (int possibleNextV = tour[fromV];
             nextV == -1 && possibleNextV != tourstart; possibleNextV = tour[possibleNextV]) {



            // calculate local gain
            g_local = broken_edge_length - edgeDistances[fromV][possibleNextV];

            // conditions that make this edge not a valid y_i
            if (!(
                    // condition 4(c)(2)
                    broken_set.count(getNormalEdge(fromV, possibleNextV)) == 0 &&
                    // condition 4(d)
                    g + g_local > 0 &&
                    // condition 4(e)
                    // x_{i+1} has never been joined before
                    joined_set.count(getNormalEdge(lastPossibleNextV, possibleNextV)) == 0 &&
                    tour[possibleNextV] != 0 && // not already joined to start
                    possibleNextV != tour[fromV] // not the one already joined to fromV
            )) {
                lastPossibleNextV = possibleNextV;
                continue;
            }

            // If we are here, then y_i := (fromV, possibleNextV)
            nextV = possibleNextV;

        }

        // a next y_i exists
        if (nextV != -1) {

            // add to our broken_set and joined_set
            broken_set.insert(broken_edge);
            joined_set.insert(getNormalEdge(fromV, nextV));

            // condition 4(f)
            y_opt_length = edgeDistances[fromV][tourstart]; // y_i_opt

            // The tour length if we exchanged the broken edge (x_i)
            // with y_opt, (t_{2i}, t_0)
            g_opt_local = g + (broken_edge_length - y_opt_length);

            if (g_opt_local > g_opt) {

                g_opt = g_opt_local;
                tour_opt = tour;
                // join the optimal tour
                tour_opt[tourstart] = fromV;
            }



            // recalculate g
            g += broken_edge_length - edgeDistances[fromV][nextV];

            // reverse tour direction between newNextV and fromV
            // implicitly breaks x_i
            reverse(fromV, lastPossibleNextV);

            // remember our new t_{2i+1}
            nextFromV = lastPossibleNextV;


            // build y_i
            tour[fromV] = nextV;

            // set new fromV to t_{2i+1}
            // and out lastNextV to t_{2i}
            lastNextV = nextV;
            fromV = nextFromV;

        }

    } while (nextV != -1);


    // join up

    tour = tour_opt;
    long distanceAfter = currentTourDistance();
    assert(distanceAfter <= initialTourDistance);

//    showTour();
    assert(isTour());

}

void LK::compareOptmize() {

    int diff;
    int old_distance = 0;
    int new_distance = 0;

    for (int j = 0; j < 100; j++) {
        for (int i = 0; i < size; i++) {
            edgeMove(i);
        }
        new_distance = currentTourDistance();
        diff = old_distance - new_distance;
        if (j != 0) {
            assert(diff >= 0);
            if (diff == 0) {
                //cout << "Converged after " << j << " iterations" << endl;
                break;
            }
        };
        old_distance = new_distance;
    }
}

void LK::reverse(int start, int end) {
    int current = start;
    int next = tour[start];
    int nextNext;
    do {
        //cout << "reversing" << endl;
        // look ahead to where we need to go after this iteration
        nextNext = tour[next];

        // reverse the direction at this point
        tour[next] = current;

        // move to the next pointer
        current = next;
        next = nextNext;
    } while (current != end); // terminate once we've reversed up to end
}

bool LK::isTour() {
    int count = 1;
    int start = tour[0];
    while (start != 0) {
        start = tour[start];
        count++;
    }
    return (count == size);
}

void LK::showTour() {
    int current = 0;
    do {
        cout << current << endl;
        current = tour[current];
    } while (current != 0);
    //cout << endl;
}

void LK::showTourIds() {
    int current = 0;
    do {
        cout << id[current] << endl;
        current = tour[current];
    } while (current != 0);
}


