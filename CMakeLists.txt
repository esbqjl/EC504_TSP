cmake_minimum_required(VERSION 3.19)
project(EC504_TSP)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(EC504_TSP
#        include/Christofield.h
#        include/ChristofieldDouble.h
        include/dynamic_programming.h
#        include/Kruskal.h
#        include/KruskalDouble.h
        include/LK_alo.h
        include/parser.h
        include/Path.h
        include/simulated_annealing.h
#        src/Christofield.cpp
#        src/ChristofieldDouble.cpp
#        src/Kruskal.cpp
#        src/KruskalDouble.cpp
        src/LK_alo.cpp
        src/main.cpp
#        src/NN.cpp
        src/parser.cpp
        src/Path.cpp
        src/simulated_annealing.cpp)
