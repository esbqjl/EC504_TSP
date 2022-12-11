#include <iostream>
#include <math.h>
#include "../include/Path.h"

using std::cout;
using std::endl;

void swap_node(Node &n1, Node &n2)
{
    Node temp;
    temp = n1;
    n1 = n2;
    n2 = temp;
}

void print_node(Node &n)
{
    printf("Node %d: x = %0.2lf, y = %0.2lf\n", n.id, n.x, n.y);
}

double compute_dist(Node n1, Node n2)
{
    double dx = n1.x - n2.x;
    double dy = n1.y - n2.y;
    return sqrt(dx * dx + dy * dy);
}

Path::Path(int num_nodes, Node* node_list)
{
    m_length = 0;
    m_num_nodes = num_nodes;
    m_node_list = new Node [m_num_nodes];

    for (int i = 0; i < m_num_nodes; i++)
    {
        m_node_list[i].id = node_list[i].id;
        m_node_list[i].x = node_list[i].x;
        m_node_list[i].y = node_list[i].y;
    }
}

Path::~Path()
{
    delete m_node_list;
}

double Path::get_length()
{
    return m_length;
}

int Path::get_num_nodes()
{
    return m_num_nodes;
}

Node Path::get_node(int i)
{
    return m_node_list[i];
}

void Path::reverse_path(int i, int j)
{
    int length = j - i + 1;
    int mid_point = i + (length / 2);

    int left = i;
    int right = j;

    while (left < right)
    {
        swap_node(m_node_list[left], m_node_list[right]);
        left++;
        right--;
    }

    //for (int k = i; k <= mid_point; k++)
    //{
    //    swap_node(m_node_list[k], m_node_list[j - k + 1]);
    //}
    
}

void Path::print_path()
{
    cout << "Printing path, nodes = " << m_num_nodes << ", path length = " << m_length << endl;
    for (int i = 0; i < m_num_nodes; i++)
    {
        print_node(m_node_list[i]);
    }
}

double Path::calc_and_update_length()
{
    m_length = 0;
    for (int i = 0; i < m_num_nodes - 1; i++)
    {
        m_length += compute_dist(m_node_list[i], m_node_list[i+1]);
    }
    m_length += compute_dist(m_node_list[0], m_node_list[m_num_nodes - 1]);

    return m_length;
}

void Path::knuth_shuffle()
{
    for (int i = 0; i <= m_num_nodes - 2; i++)
    {
        int j = i + uniform(m_num_nodes - i);
        swap_node(m_node_list[i], m_node_list[j]);
    }
}

int uniform(int m)
{
    return rand() % m;
}