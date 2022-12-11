#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "../include/Path.h"

using std::string;

int file_parser(string file_to_read, int num_cities, Node* node_list, bool debug);

#endif // PARSER_H
