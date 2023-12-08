#include "graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;


bool IsClique(const vector<int>& clique, const vector<vector<int>>& graph) {
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

void FindClique(vector<int>& current, vector<int>& maximum, const vector<vector<int>>& graph, int start = 0) {
    #pragma omp parallel for
    for (int i = start; i < graph.size(); ++i) {
        current.push_back(i);
        if (IsClique(current, graph) && current.size() > maximum.size()) {
            #pragma omp critical
            {
                if (current.size() > maximum.size()) {
                    maximum = current;
                }
            }
        }
        FindClique(current, maximum, graph, i + 1);
        current.pop_back();
    }
}

vector<int> FindMaximumClique(vector<vector<int>>& graph) {
    vector<int> current, maximum;
    FindClique(current, maximum, graph);
    return maximum;
}
