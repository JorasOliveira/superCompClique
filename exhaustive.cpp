#include "graph.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

void FindClique(vector<int>& current, vector<int>& maximum, const vector<vector<int>>& graph, int start = 0) {
    for (int i = start; i < graph.size(); ++i) {
        current.push_back(i);
        if (IsClique(current, graph) && current.size() > maximum.size()) {
            maximum = current;
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

// //BRON-KERBOSCH ALGORYTHM
// tentei aplicar este algoritmo porem nao sei se esta correto, 
// retorna um clique maior doque o retornado no codigo fornecido pelo professor

// // Structure to represent a node in the graph
// struct Node {
//   int id;
//   vector<int> neighbors;

//   // Constructor that takes an ID
//   Node(int id) {
//     this->id = id;
//   }
// };

// // Function to check if all neighbors of a node are in the clique
// bool allNeighborsPresent(const Node& node, const vector<Node>& clique) {
//   for (const Node& neighbor : node.neighbors) {
//     if (!binary_search(clique.begin(), clique.end(), neighbor)) {
//       return false;
//     }
//   }
//   return true;
// }

// void bronKerbosch(const vector<Node>& graph, vector<Node>& clique, vector<Node>& p, vector<Node>& x) {
//   // Base case: if P and X are empty, we have found a maximal clique
//   if (p.empty() && x.empty()) {
//     cout << "Maximal Clique: ";
//     for (const Node& node : clique) {
//       cout << node.id << " ";
//     }
//     cout << endl;
//     return;
//   }

//   // Choose a pivot element
//   Node pivot = p[0];

//   // For each element in P
//   for (auto it = p.begin(); it != p.end();) {
//     Node node = *it;

//     // Check if all its neighbors are present in P and Clique
//     if (allNeighborsPresent(node, clique)) {
//       // Move the element from P to Clique
//       clique.push_back(node);
//       p.erase(it);

//       // Recursively explore further possibilities
//       bronKerbosch(graph, clique, p, x);

//       // Backtrack: remove the element from Clique and move it to X
//       clique.pop_back();
//       x.push_back(node);
//     } else {
//       // Move the element from P to X
//       it = p.erase(it);
//       x.push_back(node);
//     }
//   }
// }

// int main() {
//   // Read the graph input
//   string filename;
//   int numVertices;

//   cout << "Enter the name of the graph file: ";
//   cin >> filename;

//   vector<std::vector<int>> adjMatrix = readGraph(filename, numVertices);

//   // Convert adjacency matrix to nodes and neighbors
//   vector<Node> graph;
//     for (int i = 0; i < numVertices; ++i) {
//         graph.push_back(Node(i));
//         for (int j = 0; j < numVertices; ++j) {
//             if (adjMatrix[i][j] == 1) {
//             // Use the ID to access the corresponding Node object
//             Node& neighbor = graph[j];
//             graph[i].neighbors.push_back(neighbor);
//             }
//         }   
//     }

//   // Initialize variables for Bron-Kerbosch algorithm
//   vector<Node> clique;
//   vector<Node> p;
//   vector<Node> x;

//   // Initialize p with nodes from the graph
//   for (auto& node : graph) {
//     p.push_back(node);
//   }

//   // Start the Bron-Kerbosch search
//   bronKerbosch(graph, clique, p, x);

//   return 0;
// }



//tentativa minha de criar um algoritmo recursivo,
//nao esta funcionando e nao tive tempo de continuar debugando.

//RECURSIVE ALGORYTHM
// for each vertex v in graph
//  if there is an adjacent vertex w, add w to the clique list, call the function again with the new list and w
//  the next adjacent verte is the initial vertex, return the clique list 
//  if there is no adjacent vertex w, return the clique list
//  if the size of the clique list is greater than the size of the maximum clique, set the maximum clique to the clique list
// TODO helper function that return adjacent vertexies from a given vertex
//  

// branch and bound
// still wrong

// int Degree(int v, const vector<vector<int>>& graph) {
//     return GetAdjacentVertices(v, graph).size();
// }

// int UpperBound(int v, const vector<vector<int>>& graph) {
//     return 1 + Degree(v, graph);
// }

// void FindClique(int v, vector<int>& current, vector<int>& maximum, const vector<vector<int>>& graph) {
//     current.push_back(v);
//     if (current.size() > maximum.size()) {
//         maximum = current;
//     }
//     vector<int> adjacent = GetAdjacentVertices(v, graph);
//     sort(adjacent.begin(), adjacent.end(), [&](int a, int b) {
//         return Degree(a, graph) > Degree(b, graph);
//     });
//     for (int w : adjacent) {
//         if (find(current.begin(), current.end(), w) == current.end() && UpperBound(w, graph) > maximum.size()) {
//             FindClique(w, current, maximum, graph);
//         }
//     }
//     current.pop_back();
// }




