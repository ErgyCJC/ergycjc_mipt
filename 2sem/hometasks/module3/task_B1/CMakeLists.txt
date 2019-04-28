cmake_minimum_required (VERSION 3.08)
project (SalesmanProblem-2)

set (CMAKE_CXX_STANDARD 11)
include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/headers")
include_directories ("${PROJECT_SOURCE_DIR}/tests")

add_executable (salesman src/main.cpp 
                            src/DSU.cpp
                            headers/DSU.h
                            headers/Graph.h
                            src/Graph.cpp
                            src/MST.cpp
                            headers/MST.h
                            tests/test.h
                            tests/test.cpp
                            src/Salesman.cpp
                            headers/Salesman.h
                            src/ExhaustiveSolver.cpp
                            headers/ExhaustiveSolver.h)