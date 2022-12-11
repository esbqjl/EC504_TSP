/*
* EC504 Team 1: Traveling Salesman Problem
* Author: Nicholas Sacco
* Description: Using Simulated Annealing to generate good approximate solutions 
*              to the Traveling Salesman Problem (TSP).  The algorithm and
*              proposed parameters are based on the paper "Simulated Annealing"
*              by Per Brinch Hansen, 1992.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <random>
#include <math.h>
#include "../include/parser.h"
#include "../include/Path.h"

using std::cout;
using std::endl;
using std::string;

bool DEBUG_FLAG = false;

void simulated_annealing(Path& path, double start_temp, double alpha, int num_steps, int num_attempts, int num_changes, int debug_freq, bool log_run, string log_file)
{
    std::ofstream outfile;

    double temperature = start_temp;
    int num_cities = path.get_num_nodes();
    for (int t = 0; t < num_steps; t++)
    {
        int na = 0;
        int nc = 0;

        while (na < num_attempts && nc < num_changes)
        {
            int rand1 = rand() % num_cities;
            int rand2 = rand() % num_cities;

            while (rand2 == rand1)
            {
                rand2 = rand() % num_cities;
            }

            int i = std::min(rand1, rand2);
            int j = std::max(rand1, rand2);

            int si = (i + 1 % num_cities);
            int sj = (j + 1 % num_cities);

            double dE = compute_dist(path.get_node(i), path.get_node(j)) 
                        + compute_dist(path.get_node(si), path.get_node(sj)) 
                        - compute_dist(path.get_node(i), path.get_node(si)) 
                        - compute_dist(path.get_node(j), path.get_node(sj));

            bool accept_update;
            if (dE > 0)
            {
                double accept_prob = exp(-dE / temperature);
                double rand_num = ((double)rand() / RAND_MAX);
                accept_update = accept_prob > rand_num;
                /*if (t == 0)
                {
                    cout << "dE = " << dE << endl;
                    printf("Accept prob = %e, rand num = %e, accept = %d\n", accept_prob, rand_num, accept_update);
                }*/
                
            }
            else if (dE < 0)
            {
                accept_update = true;
            }

            if (accept_update)
            {
                //path.print_path();
                //cout << "Reversing nodes " << si << " to " << j << endl;
                path.reverse_path(si, j);
                //path.print_path();
                nc++;
                //printf("Accepted dE = %lf\n", dE);
            }
            na++;
        }
        if (debug_freq > 0 && (t % int(num_steps/debug_freq) == 0))
            printf("Iteration (%d/%d) complete at temperature %lf, made %d attempts and accepted %d changes\n", t, num_steps-1, temperature, na, nc);
        temperature *= alpha;

        if (log_run)
        {
            if (t == 0)
            {
                outfile.open(log_file);
            }
            else
            {
                outfile.open(log_file, std::ios_base::app);
            }

            for (int i = 0; i < num_cities; i++)
            {
                outfile << path.get_node(i).id << ",";
            }
            outfile << temperature << "," << na << "," << nc << endl;
            outfile.close();
        }


    }
}

void run_suite(Node* node_list, int num_cities, int num_experiments, double start_temp, double alpha, int num_steps, int num_attempts, int num_changes, int debug_freq, string write_file)
{
    std::ofstream outfile;
    std::chrono::time_point<std::chrono::steady_clock> start, stop; 
    std::chrono::duration<double> difference_in_time;
    
    double annealing_run_time_sec; 

    for (int t = 0; t < num_experiments; t++)
    {
        cout << "RUNNING EXPERIMENT t = " << t << endl;

        Path m_path(num_cities, node_list);
        m_path.knuth_shuffle();

        start = std::chrono::steady_clock::now();
        simulated_annealing(m_path, start_temp, alpha, num_steps, num_attempts, num_changes, debug_freq, false, "None");
        stop = std::chrono::steady_clock::now();
        difference_in_time = stop - start;
        annealing_run_time_sec = double(difference_in_time.count());
        
        double stopping_distance = m_path.calc_and_update_length();
        cout << "Stopping distance = " << stopping_distance << endl;
        
        if (t == 0)
        {
            outfile.open(write_file);
            outfile << "#," << num_cities << "," << start_temp << "," << alpha << "," << num_steps << "," << num_attempts << "," << num_changes << endl;
        }
        else
        {
            outfile.open(write_file, std::ios_base::app);
        }
       
        for (int i = 0; i < num_cities; i++)
        {
            outfile << m_path.get_node(i).id << ",";
        }
        outfile << stopping_distance << "," << annealing_run_time_sec << endl;
        outfile.close();
    }
}
