#pragma once

#include <array>
#include "stack.h"


// --- "using" types

// linked list consists of vertex/distance pair
template<size_t vertices>
using AdjList = std::array<SingleList<std::pair<int, int>>, vertices>;

// array consists of distance/parent pair
template<size_t t_vertices>
using PathTable = std::array<std::pair<int, int>, t_vertices>;

template<size_t t_vertices>
using PathTables = std::array<PathTable<t_vertices>, t_vertices>;


// Adjacency List Non-Directional Graph
template<size_t t_vertices>
class AdjListNonDirGraph
{
private:

    // --- Member variables

    AdjList<t_vertices> m_vertices;
    PathTables<t_vertices> m_min_paths;


    // --- Helper methods

    auto findMin(std::array<std::pair<int, int>, t_vertices> &l_shortest_path,
                 std::array<bool, t_vertices> &l_visited)
    {
        int min_index = -1;

        for (size_t i = 0; i < l_shortest_path.size(); ++i) {
            if (!l_visited[i]) {
                if (min_index == -1) {
                    min_index = static_cast<int>(i);
                }

                if (l_shortest_path[static_cast<size_t>(min_index)].first
                    > l_shortest_path[i].first) {
                    min_index = static_cast<int>(i);
                }
            }
        }

        return min_index;
    }

    void initDistanceArray(size_t l_index)
    {
        m_min_paths[l_index].fill({INT_MAX, -1});
        m_min_paths[l_index][l_index].first = 0;
    }

    // dijkstra algorithm
    void findShortestPaths()
    {
        for (size_t i = 0; i < t_vertices; ++i) {
            initDistanceArray(i);

            std::array<bool, t_vertices> visited_vertices;
            for (auto &visited_vert : visited_vertices) {
                visited_vert = false;
            }

            while (true) {
                auto min_index = findMin(m_min_paths[i], visited_vertices);
                if (min_index == -1) {
                    break;
                }

                auto &min = m_min_paths[i][static_cast<size_t>(min_index)];
                for (auto &neighbour : m_vertices[static_cast<size_t>(min_index)]) {
                    auto &vert_dist_pair = m_min_paths[i][static_cast<size_t>(neighbour.first)];
                    if (vert_dist_pair.first > neighbour.second + min.first) {
                        vert_dist_pair.first = neighbour.second + min.first;
                        vert_dist_pair.second = min_index;
                    }
                }
                visited_vertices[static_cast<size_t>(min_index)] = true;
            }
        }
    }


public:

    // C/D-tors

    AdjListNonDirGraph() = default;
    AdjListNonDirGraph(const AdjListNonDirGraph &) = delete;


    // --- Member functions

    bool insert_edge(int l_vert1, int l_vert2, int weight)
    {
        auto &vert1_neighbours = m_vertices[static_cast<size_t>(l_vert1)];
        auto &vert2_neighbours = m_vertices[static_cast<size_t>(l_vert2)];
        auto itr = vert1_neighbours.find({l_vert2, weight});
        if (itr == vert1_neighbours.end()) {
            vert1_neighbours.push_back({l_vert2, weight});
            vert2_neighbours.push_back({l_vert1, weight});
            return true;
        }

        return false;
    }

    void finalize()
    {
        findShortestPaths();
    }

    auto getShortestPath(size_t l_vert1, size_t l_vert2) const
    {
        Stack<int> path;
        if (m_min_paths[l_vert1][l_vert2].first != INT_MAX) {
            path.push(static_cast<int>(l_vert2));
            while (static_cast<size_t>(path.top()) != l_vert1) {
                path.push(m_min_paths[l_vert1][static_cast<size_t>(path.top())].second);
            }
        }

        return std::move(path);
    }

};
