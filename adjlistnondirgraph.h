#pragma once

#include <vector>
#include <bits/c++io.h>
#include "stack.h"


// --- "using" types

// linked list consists of vertex/distance pair
using AdjList = std::vector<CircSingleList<std::pair<int, int>>>;

// array consists of distance/parent pair
using PathTable = std::vector<std::pair<int, int>>;


// Adjacency List Non-Directional Graph
class AdjListNonDirGraph
{
private:

    // --- Member variables

    AdjList m_vertices;
    std::vector<PathTable> m_min_paths;


    // --- Helper methods

    int findMin(std::vector<std::pair<int, int>> &l_shortest_path,
                 std::vector<bool> &l_visited);
    void initDistanceArray(size_t l_index);
    void findShortestPaths(); // dijkstra algorithm


public:

    // --- C/D-tors

    AdjListNonDirGraph() = default;
    AdjListNonDirGraph(const AdjListNonDirGraph &) = delete;
    AdjListNonDirGraph(AdjListNonDirGraph &&) = default;


    // --- Member functions

    Stack<int> getShortestPath(size_t l_vert1, size_t l_vert2) const;
    bool insertEdge(size_t l_vert1, size_t l_vert2, int weight);
    void finalize();

};
