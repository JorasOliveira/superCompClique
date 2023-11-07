#ifndef GRAPH_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define GRAPH_H
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <fstream>
#include <omp.h>
// #include <mpi.h>
using namespace std;


#include <string>
#include <vector>

const std::string FILE_NAME = "graph.txt";
int NUM_VERTICES = 1000;

vector<vector<int>> readGraph(const string& FILE_NAME, int& NUM_VERTICES);

vector<int> FindMaximumClique(vector<vector<int>> graph, int NUM_VERTICES);


#endif