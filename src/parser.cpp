#include <iostream>
#include <fstream>
#include "../include/Path.h"
#include "../include/parser.h"

int file_parser(string file_to_read, int num_cities, Node* node_list, bool debug)
{
    // Now start to read the contents of the file

    std::ifstream infile;

    infile.open(file_to_read);
    if (!infile)
    {
        cout << "Error opening file" <<endl;
        return -1;
    } 
  
    string read_line;

    int start_row = 1;
    std::getline(infile, read_line);
    start_row++;

    while (read_line != "NODE_COORD_SECTION")
    {
        std::getline(infile, read_line); 
        start_row++;
    }
    cout << "START ROW = " << start_row << endl;

    for (int i = start_row; i < start_row + num_cities; i++)
    {
        std::getline(infile, read_line);

        size_t first_space = read_line.find_first_of(" ");
        size_t second_space = read_line.find_last_of(" ");

        node_list[i - start_row].id = std::stoi(read_line.substr(0, first_space)) - 1;
        node_list[i - start_row].x = std::stof(read_line.substr(first_space, second_space));
        node_list[i - start_row].y = std::stof(read_line.substr(second_space, string::npos));

        if (debug)
            cout << "Node " << node_list[i - start_row].id << ", x = " << node_list[i - start_row].x << ", y = " << node_list[i - start_row].y << endl;  
    }

    infile.close();

    return 0;

}



