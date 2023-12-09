#include "graph.h"
#include <mpi.h>
#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>

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
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    vector<int> current, maximum;
    double start_time = MPI_Wtime();

    //dividimos o grafo em partes iguais para cada processo
    int nodes_per_process = graph.size() / size;
    int start_node = rank * nodes_per_process;
    int end_node = (rank + 1) * nodes_per_process;
    if (rank == size - 1) {
        end_node = graph.size();
    }
    
    vector<vector<int>> local_graph(nodes_per_process);
    MPI_Scatter(&graph[0], nodes_per_process * graph.size(), MPI_INT, &local_graph[0], nodes_per_process * graph.size(), MPI_INT, 0, MPI_COMM_WORLD);

    //cada processo encontra o clique maximo local em seu subgrafo
    for (int i = start_node; i < end_node; ++i) {
        current.push_back(i);
        if (IsClique(current, graph) && current.size() > maximum.size()) {
            maximum = current;
        }
        FindClique(current, maximum, graph, i + 1);
        current.pop_back();
    }

    //juntamos os cliques maximos locais em um vetor
    vector<vector<int>> all_cliques;
    if (rank == 0) {
        all_cliques.resize(size);
    }
    MPI_Gather(&maximum, maximum.size(), MPI_INT, &all_cliques[0], maximum.size(), MPI_INT, 0, MPI_COMM_WORLD);

    //acha o cloque maixmo global
    if (rank == 0) {
        for (int i = 1; i < size; ++i) {
            if (all_cliques[i].size() > maximum.size()) {
                maximum = all_cliques[i];
            }
        }
        double end_time = MPI_Wtime();
        std::cout << "Execution time (MPI): " << (end_time - start_time) << " seconds" << std::endl;
    }

    MPI_Finalize();
    return maximum;
}
