#include "graph.h"
int main() {

    vector<vector<int>> graph = readGraph(FILE_NAME, NUM_VERTICES);

    vector<int> maximumClique = FindMaximumClique(graph, NUM_VERTICES);

    return 0;
}
