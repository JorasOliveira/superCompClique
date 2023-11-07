#include "graph.h"

vector<int> FindMaximumClique(vector<vector<int>> graph, int numVertices) {
    vector<int> maximumClique;
    vector<int> candidates;

    for (int i = 0; i < numVertices; i++) {
        candidates.push_back(i);
    }

    while (!candidates.empty()) {
        int v = candidates.back();
        candidates.pop_back();

        bool canAdd = true;

        for (int u : maximumClique) {
            if (graph[u][v] == 0) {
                canAdd = false;
                break;
            }
        }

        if (canAdd) {
            maximumClique.push_back(v);
            vector<int> newCandidates;

            for (int u : candidates) {
                bool adjacentToAll = true;

                for (int c : maximumClique) {
                    if (graph[u][c] == 0) {
                        adjacentToAll = false;
                        break;
                    }
                }

                if (adjacentToAll) {
                    newCandidates.push_back(u);
                }
            }

            candidates = newCandidates;
        }
    }

    return maximumClique;
}
