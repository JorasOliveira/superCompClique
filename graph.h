#ifndef GRAPH_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define GRAPH_H
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <fstream>
#include <omp.h>
#include <string>
// #include <mpi.h>
using namespace std;

std::vector<std::vector<int>> readGraph(const std::string& fileName, int& numVertices);

std::vector<int> FindMaximumClique(std::vector<std::vector<int>> &graph);


#endif