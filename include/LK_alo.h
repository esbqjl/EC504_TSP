//
// Created by Nelson Wang on 11/29/22.
//

#ifndef EC504_TSP_LK_ALO_H
#define EC504_TSP_LK_ALO_H
#include <vector>
using namespace std;

class LK{
public:
    int size;
    LK(vector<pair<double,double> >&locate,vector<int>&id);
    double currentTourDistance();
    void compareOptmize();
    void showTour();
    void showTourIds();


private:
    vector<int> tour;
    vector<vector<double> > edgeDistances;
    vector<vector<int> > edgeSign;
    vector<pair<double, double> > locate ;
    vector<int> id;
    void edgeMove(int tourStart);
    void reverse(int start, int end);
    bool isTour();



};



#endif //EC504_TSP_LK_ALO_H
