
# Travelling Salesman Problem

To compile the code, run:

g++ ./src/*.cpp -o run -std=c++11

For BU SCC if any errors out, try to run(it's same as above):

g++ -std=gnu+11 ./src/*.cpp -o run    

For some algorithm, please run multiple .cpp file

For example: 

g++ main.cpp Christofield.cpp Kruskal.cpp LK_alo.cpp Path.cpp simulated_annealing.cpp parser.cpp -o run -std=c++11

To run the code, run:

./run ./test_data/<file_name>.tsp

As an example:

./run ./test_data/ei8246.tsp

The report of TSP:
https://docs.google.com/document/d/14It91J9HPuKrDFEN3TjJE2UVgA-5rP6UmvM6H2LXd7o/edit
