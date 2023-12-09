#include "graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>
#include <bitset>

using namespace std;

// Checa se a clique é válida
bool IsClique(const vector<int>& clique, const vector<vector<int>>& graph) { 
    bool all_edges = true; // assume que todos os vertices sao adjacentes

    #pragma omp for
    for (int i = 0; i < clique.size(); ++i) {
        for (int j = i + 1; j < clique.size(); ++j) {
            if (graph[clique[i]][clique[j]] == 0) { // se nao houver aresta entre os vertices, nao eh um clique
                all_edges = false;
                break;
            }
        }
        if (!all_edges) { // se nao for um clique, nao precisa continuar checando
            break;
        }
    }

    return all_edges; // retorna true se todos os vertices forem adjacentes
}

// Encontra a clique máxima
double FindClique(vector<int>& current, vector<int>& maximum, const vector<vector<int>>& graph, int start = 0) {
    auto start_time = std::chrono::high_resolution_clock::now();

    // vetor de boolenaos com tamanho fixo para evitar realocacao de memoria
    std::vector<bool> visited(graph.size(), false); 

    #pragma omp parallel for
    for (int i = start; i < graph.size(); ++i) { // para cada vertice no grafo
        if (!visited[i]) { // Ignora nos ja visitados para evitar trabalho redundante
            visited[i] = true; // marca no atual como visitado
            current.push_back(i);

            // checa se o clique atual eh de fato um clique valido
            if (IsClique(current, graph)) {
                // update sse o clique atual eh maior que o maximo
                #pragma omp critical
                {
                    if (current.size() > maximum.size()) {
                        maximum = current;
                    }
                }

                // recursao para explorar os nos adjacentes
                if (current.size() < graph.size()) { // se o clique atual nao for o maior possivel, continua explorando
                    FindClique(current, maximum, graph, i + 1);
                }
            }

            visited[i] = false; // desmarca no atual como visitado, caso nao seja um clique valido
            current.pop_back();
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    double total_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    return total_time;
}

vector<int> FindMaximumClique(vector<vector<int>>& graph) {
    vector<int> current, maximum;
    double tempo = FindClique(current, maximum, graph);
    std::cout << "Tempo de execução: " << tempo * 1e-6 << " segundos" << std::endl;
    return maximum;
}
