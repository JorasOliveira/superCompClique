#include "graph.h"

int main() {

    std::string fileName = "graph.txt";
    int numVertices = 300;

    vector<vector<int>> graph = readGraph(fileName, numVertices);
    vector<int> maximumClique = FindMaximumClique(graph);

    // Print the maximum clique
    for (int i = 0; i < maximumClique.size(); i++) {
        cout << maximumClique[i] << " ";
    }
    cout << endl;

    return 0;
}
