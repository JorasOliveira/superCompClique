#include "graph.h"

int main() {

    std::string fileName = "graph.txt";
    int numVertices = 300;

    vector<vector<int>> graph = readGraph(fileName, numVertices);
    vector<int> maximumClique = FindMaximumClique(graph);

    // Print the maximum clique
    for (int i = 0; i < maximumClique.size(); i++) {
        cout << "Clique maximo encontrado: " +  maximumClique[i] + 1 << " "; // +1 para imprimir o valor correto baseado no arquivo do professor
    }
    cout << endl;

    return 0;
}
