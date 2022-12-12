#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <iomanip>
#include "../include/Christofield.h"
#include "../include/dynamic_programming.h"
#include "../include/LK_alo.h"
#include "../include/Path.h"
#include "../include/parser.h"
#include "../include/simulated_annealing.h"

using std::cout;
using std::endl;
using std::string;

bool DEBUG_FLAG = false;
int MAX_CITIES = 50000;

vector<int> id;
vector<pair<double, double> > locate;

//typedef struct Node
//{
//    int id;
//    double x;
//    double y;
//
//} Node;


int main(int argc, char* argv[])
{
    string full_file_path(argv[1]);
    string file_name = full_file_path.substr(full_file_path.find_last_of("/") + 1, full_file_path.back());
    string file_name_no_ext = file_name.substr(0, file_name.find_first_of("."));
    string file_path = full_file_path.substr(0, full_file_path.find_last_of("/") + 1);

    cout << "file_path: " << file_path << endl;
    cout << "file name: " << file_name << endl;



    string country_id = file_name.substr(0, 2);
    int NUM_CITIES = std::stoi(file_name.substr(2, file_name.find(".")));

    cout << "Country ID: " << country_id << ", Number of cities = " << NUM_CITIES << endl;

    Node* node_list = new Node[NUM_CITIES];

    int status = file_parser(argv[1], NUM_CITIES, node_list, DEBUG_FLAG);
    if (status == -1)
    {
        return -1;
    }

    if (NUM_CITIES > MAX_CITIES)
    {
        cout << "[ERROR] Too many cities to directly store distances" << endl;
        return -1;
    }

    std::ifstream infile;

    infile.open(argv[1]);
    if (!infile)
    {
        cout << "Error opening file " <<endl;
        return -1;
    }


    string read_line;

    for (int i = 0; i < START_ROW; i++)
    {
        std::getline(infile, read_line);
    }

    for (int i = START_ROW; i < START_ROW + NUM_CITIES; i++)
    {
        std::getline(infile, read_line);

        size_t first_space = read_line.find_first_of(" ");
        size_t second_space = read_line.find_last_of(" ");

        node_list[i - START_ROW].id = std::stoi(read_line.substr(0, first_space));
        node_list[i - START_ROW].x = std::stof(read_line.substr(first_space, second_space));
        node_list[i - START_ROW].y = std::stof(read_line.substr(second_space, string::npos));

        if (DEBUG_FLAG)
            cout << "Node " << node_list[i - START_ROW].id << ", x = " << node_list[i - START_ROW].x << ", y = " << node_list[i - START_ROW].y << endl;
    }

    infile.close();
    double* distance_sq_matrix = new double[NUM_CITIES * NUM_CITIES];

    for (int i = 0; i < NUM_CITIES; i++)
    {
        if (i % (NUM_CITIES/10) == 0)
        {
            cout << "Computing distances for node " << i << endl;
        }

        for (int j = i + 1; j < NUM_CITIES; j++)
        {
            double dij_sq = (node_list[i].x - node_list[j].x) * (node_list[i].x - node_list[j].x) + (node_list[i].y - node_list[j].y) * (node_list[i].y - node_list[j].y);
            distance_sq_matrix[NUM_CITIES * i + j] = dij_sq;
            distance_sq_matrix[NUM_CITIES * j + i] = dij_sq;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << std::setprecision(2) << std::setw(8) << distance_sq_matrix[NUM_CITIES * i + j] << " ";
        }
        cout << endl;
    }




    /* ALGORITHM 1: DYNAMIC PROGRAMMING */


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

    dp(c,NUM_CITIES);


    // -------------------------------------------------------------------------

    /* ALGORITHM 2: SIMULATED ANNEALING */

    // SIMULATED ANNEALING PARAMETERS - FEASIBLE PARAMETERS
    // Run with these parameters if you want "quick" results
    double TMAX = sqrt(NUM_CITIES);
    double alpha = 0.95;
    int STEPS = ceil(50 * log(NUM_CITIES));
    int ATTEMPTS = 100 * NUM_CITIES;
    int CHANGES = 10 * NUM_CITIES;
    int DEBUG_FREQ = 10;
    int NUM_EXPERIMENTS = 30;
//
//
//
    string write_file = file_path + "/results/" + file_name_no_ext + "_tours.csv";
    string log_file = file_path + "/results/" + file_name_no_ext + "_log.csv";
//
//    // Run NUM_EXPERIMENTS on the list of NUM_CITIES cities using the above parameters; write final path and run-time
//    // data to directory.  This might take a while... I recommend running on datasets no larger than the ei8246.tsp
//    // dataset...it also dumps a LOT of data into a CSV, I DO NOT RECOMMEND OPENING THE CSV, unless it is the wi29.tsp
//    // dataset.  MATLAB scripts have been provided for visualizing the results.
    run_suite(node_list, NUM_CITIES, NUM_EXPERIMENTS, TMAX, alpha, STEPS, ATTEMPTS, CHANGES, DEBUG_FREQ, write_file);

    Path m_path(NUM_CITIES, node_list);
//
//    // This runs a single simulated annealing experiment on the list of NUM_CITIES cities using the above parameters;
//    // the path AT EACH ITERATION is written to a CSV file; I ALSO DO NOT RECOMMEND OPENING THE CSV.  MATLAB scripts
//    // have been provided for visualizing the results.
//    simulated_annealing(m_path, TMAX, alpha, STEPS, ATTEMPTS, CHANGES, DEBUG_FREQ, true, log_file);
//
//    // -------------------------------------------------------------------------
//
//    /* ALGORITHM 3: LIN-KERNIGHAN */
//
//
    for(int i=0;i<NUM_CITIES;i++){
        id.push_back(node_list[i].id);
        locate.push_back(make_pair(node_list[i].x,node_list[i].y));
    }
    LK test(locate,id);
    test.compareOptmize();
    test.showTourIds();
//
//
//    // -------------------------------------------------------------------------
//
//    /* ALGORTIHM 4: kNN */
    int* completed = new int[NUM_CITIES];
    for(int i = 0 ; i < NUM_CITIES; i++){
        completed[i] = 0;
    }

    std::ofstream outfile("result.txt");
    int place = 0;
    int count = 0;

    outfile << node_list[place].id << endl;
    completed[place] = 1;
    count ++;
    while(count < NUM_CITIES) {
        double min = DBL_MAX;
        int temp;
        for (int i = 0; i < NUM_CITIES; i++) {
            if (i != place && completed[i] == 0 && distance_sq_matrix[place * NUM_CITIES + i] < min) {
                min = distance_sq_matrix[place * NUM_CITIES + i];
                temp = i;
            }
        }
        place = temp;
        outfile << node_list[place].id << endl;
        completed[place] = 1;
        count ++;

    }
    outfile.close();

    delete[] completed;
//
//    // -------------------------------------------------------------------------
//
//    /* ALGORITHM 5: CHRISTOFIDES */
//
//


    // -------------------------------------------------------------------------

    delete node_list;
    delete distance_sq_matrix;


    return 0;

}