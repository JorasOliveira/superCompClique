#include "graph.h"

vector<int> FindMaximumClique(vector<vector<int>> &graph) {
    int numVertices = graph.size();
    vector<int> maximumClique;

    // Sort vertices by degree (number of neighbors)
    vector<pair<int, int>> verticesWithDegree;
    for (int i = 0; i < numVertices; ++i) {
        int degree = count(graph[i].begin(), graph[i].end(), 1);
        verticesWithDegree.push_back({degree, i});
    }

    sort(verticesWithDegree.rbegin(), verticesWithDegree.rend());

    // Greedy approach: Add vertices to the clique in order of decreasing degree
    for (const auto &vertex : verticesWithDegree) {
        int v = vertex.second;

        bool canAdd = true;
        for (int u : maximumClique) {
            if (graph[u][v] == 0) {
                canAdd = false;
                break;
            }
        }

        if (canAdd) {
            maximumClique.push_back(v);
        }
    }

    return maximumClique;
}







// vector<int> FindMaximumClique(vector<vector<int>> &graph) {
//     vector<int> maximumClique;
//     vector<int> candidates;

//     for (int i = 0; i < graph.size(); i++) {
//         candidates.push_back(i);
//     }

//     while (!candidates.empty()) {
//         int v = candidates.back();
//         candidates.pop_back();

//         bool canAdd = true;

//         for (int u : maximumClique) {
//             if (graph[u][v] == 0) {
//                 canAdd = false;
//                 break;
//             }
//         }

//         if (canAdd) {
//             maximumClique.push_back(v);
//             vector<int> newCandidates;

//             for (int u : candidates) {
//                 bool adjacentToAll = true;

//                 for (int c : maximumClique) {
//                     if (graph[u][c] == 0) {
//                         adjacentToAll = false;
//                         break;
//                     }
//                 }

//                 if (adjacentToAll) {
//                     newCandidates.push_back(u);
//                 }
//             }

//             candidates = newCandidates;
//         }
//     }

//     return maximumClique;
// }














// vector<int> FindMaximumClique(vector<vector<int>> graph, int numVertices) {
//     vector<int> maximumClique;
//     vector<int> candidates;

//     for (int i = 0; i < numVertices; i++) {
//         candidates.push_back(i);
//     }

//     while (!candidates.empty()) {
//         int v = candidates.back();
//         candidates.pop_back();

//         bool canAdd = true;

//         for (int u : maximumClique) {
//             if (graph[u][v] == 0) {
//                 canAdd = false;
//                 break;
//             }
//         }

//         if (canAdd) {
//             maximumClique.push_back(v);
//             vector<int> newCandidates;

//             for (int u : candidates) {
//                 bool adjacentToAll = true;

//                 for (int c : maximumClique) {
//                     if (graph[u][c] == 0) {
//                         adjacentToAll = false;
//                         break;
//                     }
//                 }

//                 if (adjacentToAll) {
//                     newCandidates.push_back(u);
//                 }
//             }

//             candidates = newCandidates;
//         }
//     }

//     return maximumClique;
// }
