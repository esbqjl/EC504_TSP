#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;

typedef struct Node
{
    int id;
    double x;
    double y;

} Node;

void swap_node(Node &n1, Node &n2);

void print_node(Node &n);

double compute_dist(Node n1, Node n2);

int uniform(int m);

class Path
{
public:
    Path(int num_nodes, Node* node_list);
    ~Path();
    double get_length();
    double get_nodelist();

    Node get_node(int i);
    int get_num_nodes();

    void reverse_path(int i, int j);

    void print_path();

    double calc_and_update_length();

    void knuth_shuffle();

private:
    double m_length;
    int m_num_nodes;
    Node* m_node_list;
};


#endif // PATH_H