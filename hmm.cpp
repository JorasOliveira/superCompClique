#include "graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>


// abordagem exaustiva
bool IsClique(const vector<int>& clique, const vector<vector<int>>& graph) {
    for (int i = 0; i < clique.size(); ++i) {
        for (int j = i + 1; j < clique.size(); ++j) {
            if (graph[clique[i]][clique[j]] == 0) {
                return false;
            }
        }
    }
    return true;
}

double FindClique(vector<int>& current, vector<int>& maximum, const vector<vector<int>>& graph, int start = 0) {
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = start; i < graph.size(); ++i) {
        current.push_back(i);
        if (IsClique(current, graph) && current.size() > maximum.size()) {
            maximum = current;
        }
        double sub_time = FindClique(current, maximum, graph, i + 1);
        current.pop_back();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    double total_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    return total_time;
}

vector<int> FindMaximumClique(vector<vector<int>>& graph) {
    vector<int> current, maximum;
    double time = FindClique(current, maximum, graph);
    std::cout << "Execution time: " << time << " microseconds" << std::endl;
    return maximum;
}

// abordagem com Open MP
bool IsCliqueOMP(const vector<int>& clique, const vector<vector<int>>& graph) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < clique.size(); ++i) {
        for (int j = i + 1; j < clique.size(); ++j) {
            if (graph[clique[i]][clique[j]] == 0) {
                return false;
            }
        }
    }
    return true;
}

void FindCliqueOMP(vector<int>& current, vector<int>& maximum, const vector<vector<int>>& graph, int start = 0) {
    #pragma omp parallel for
    for (int i = start; i < graph.size(); ++i) {
        current.push_back(i);
        if (IsCliqueOMP(current, graph) && current.size() > maximum.size()) {
            #pragma omp critical
            {
                if (current.size() > maximum.size()) {
                    maximum = current;
                }
            }
        }
        FindCliqueOMP(current, maximum, graph, i + 1);
        current.pop_back();
    }
}

vector<int> FindMaximumCliqueOMP(vector<vector<int>>& graph) {
    vector<int> current, maximum;
    FindCliqueOMP(current, maximum, graph);
    return maximum;
}