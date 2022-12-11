#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <iostream>
#include <stdio.h>
#include <string>
#include "../include/Path.h"

using std::string;

void simulated_annealing(Path& path, double start_temp, double alpha, int num_steps, int num_attempts, int num_changes, int debug_freq, bool log_run, string log_file);

void run_suite(Node* node_list, int num_cities, int num_experiments, double start_temp, double alpha, int num_steps, int num_attempts, int num_changes, int debug_freq, string write_file);


#endif // SIMULATED_ANNEALING_H