cmake_minimum_required(VERSION 3.19)
project(EC504_TSP)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(EC504_TSP
<<<<<<< Updated upstream
#        include/Christofield.h
#        include/ChristofieldDouble.h
        include/dynamic_programming.h
#        include/Kruskal.h
#        include/KruskalDouble.h
=======
        include/Christofield.h
#        include/ChristofieldDouble.h
        include/dynamic_programming.h
        include/Kruskal.h
        include/KruskalDouble.h
>>>>>>> Stashed changes
        include/LK_alo.h
        include/parser.h
        include/Path.h
        include/simulated_annealing.h
<<<<<<< Updated upstream
#        src/Christofield.cpp
#        src/ChristofieldDouble.cpp
#        src/Kruskal.cpp
=======
        src/Christofield.cpp
#        src/ChristofieldDouble.cpp
        src/Kruskal.cpp
>>>>>>> Stashed changes
#        src/KruskalDouble.cpp
        src/LK_alo.cpp
        src/main.cpp
#        src/NN.cpp
        src/parser.cpp
        src/Path.cpp
        src/simulated_annealing.cpp)
