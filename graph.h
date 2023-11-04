#ifndef GRAPH_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define GRAPH_H
#include <vector>
#include <iostream>
#include <fstream>
#include <omp.h>
// #include <mpi.h>


const std::string FILE_NAME = "graph.txt";
int NUM_VERTICES = 1000;

std::vector<std::vector<int>> readGraph(const std::string& FILE_NAME, int& numVertices);


#endif