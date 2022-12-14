#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <cfloat>
#define START_ROW 7

using std::cout;
using std::endl;
using std::string;

bool DEBUG_FLAG = false;

typedef struct Node
{
    int id;
    double x;
    double y;

} Node;

//int NUM_CITIES=8246;
//int completed[8246];
//int cost = 0;
//int NUM_CITIES;
//double* distance_sq_matrix;

double NN(double* distance_sq_matrix, Node* node_list, int* completed, int NUM_CITIES);


double NN(double* distance_sq_matrix, Node* node_list, int* completed, int NUM_CITIES){
    std::ofstream outfile("result.txt");
    int place = 0;
    double cost = 0;
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
        cost += min;
    }
    outfile.close();
    cost += distance_sq_matrix[place*NUM_CITIES];
    return cost;

}


int main(int argc, char* argv[])
{
    string full_file_path(argv[1]);
    string file_name = full_file_path.substr(full_file_path.find_last_of('/') + 1, full_file_path.back());

    cout << "file name: " << file_name << endl;

    string country_id = file_name.substr(0, 2);
    int NUM_CITIES = std::stoi(file_name.substr(2, file_name.find(".")));

    cout << "Country ID: " << country_id << ", Number of cities = " << NUM_CITIES << endl;

    // Now start to read the contents of the file

    std::ifstream infile;

    infile.open(argv[1]);
    if (!infile)
    {
        cout << "Error opening file " <<endl;
        return -1;
    }

    Node* node_list = new Node[NUM_CITIES];
    int* completed = new int[NUM_CITIES];
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
        cout<< read_line<<endl;

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

    int i;
    for(i = 0 ; i < NUM_CITIES; i++){
        completed[i] = 0;
    }

    double min_cost = NN(distance_sq_matrix,node_list,completed,NUM_CITIES);
    cout << min_cost <<endl;


    delete[] node_list;
    delete[] completed;
    delete[] distance_sq_matrix;

    return 0;
}