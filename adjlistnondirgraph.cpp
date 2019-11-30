#include "adjlistnondirgraph.h"
#include <climits>

// --- Helper methods

int AdjListNonDirGraph::findMin(DynArray<std::pair<int, int>> &l_shortest_path,
                                DynArray<bool> &l_visited)
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

void AdjListNonDirGraph::initDistanceArray(size_t l_index)
{
    m_min_paths.resize(m_vertices.size());
    m_min_paths[l_index].resize(m_vertices.size(), {INT_MAX, -1});
    m_min_paths[l_index][l_index].first = 0;
}

void AdjListNonDirGraph::findShortestPaths()
{
    for (size_t i = 0; i < m_vertices.size(); ++i) {
        initDistanceArray(i);

        DynArray<bool> visited_vertices(m_vertices.size(), false);
        while (true) {
            auto min_index = findMin(m_min_paths[i], visited_vertices);
            if (min_index == -1) {
                break;
            }

            auto &min = m_min_paths[i][static_cast<size_t>(min_index)];
            for (auto &neighbour : m_vertices[static_cast<size_t>(min_index)]) {
                auto &dist_par_pair = m_min_paths[i][static_cast<size_t>(neighbour.first)];
                if (dist_par_pair.first > neighbour.second + min.first) {
                    dist_par_pair.first = neighbour.second + min.first;
                    dist_par_pair.second = min_index;
                }
            }
            visited_vertices[static_cast<size_t>(min_index)] = true;
        }
    }
}


// --- Member functions

Stack<int> AdjListNonDirGraph::getShortestPath(size_t l_vert1, size_t l_vert2) const
{
    Stack<int> path;
    if (m_min_paths[l_vert1][l_vert2].first != INT_MAX) {
        path.push(static_cast<int>(l_vert2));
        while (static_cast<size_t>(path.top()) != l_vert1) {
            path.push(m_min_paths[l_vert1][static_cast<size_t>(path.top())].second);
        }
    }

    return path;
}

bool AdjListNonDirGraph::insertEdge(size_t l_vert1, size_t l_vert2, int weight)
{
    if (m_vertices.size() < l_vert1 + 1) {
        m_vertices.resize(l_vert1 + 1);
    }

    if (m_vertices.size() < l_vert2 + 2) {
        m_vertices.resize(l_vert2 + 1);
    }

    auto &vert1_neighbours = m_vertices.at(l_vert1);
    auto &vert2_neighbours = m_vertices.at(l_vert2);
    auto itr = vert1_neighbours.find({l_vert2, weight});
    if (itr == vert1_neighbours.end()) {
        vert1_neighbours.push_back({l_vert2, weight});
        vert2_neighbours.push_back({l_vert1, weight});
        return true;
    }

    return false;
}

void AdjListNonDirGraph::finalize()
{
    findShortestPaths();
}
