cmake_minimum_required(VERSION 3.10)

# Project name
project(TSP_run)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# executable
add_executable(TSP_run ./src/main.cpp ./src/geneticAlgorithm.cpp ./src/localsearch.cpp ./src/readFile.cpp ./src/utils.cpp)
set_target_properties( TSP_run PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../ )
