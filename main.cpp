#include <iostream>
#include "adjlistnondirgraph.h"

void printPath(Stack<int> l_path)
{
    if (l_path.empty()) {
        return;
    }

    std::cout << l_path.top();
    l_path.pop();
    while (!l_path.empty()) {
        std::cout << "->" << l_path.top();
        l_path.pop();
    }
    std::cout << std::endl;
}

int main()
{
    // test graph
    AdjListNonDirGraph<5> graph;
    graph.insert_edge(0, 2, 2);
    graph.insert_edge(0, 4, 6);
    graph.insert_edge(1, 2, 7);
    graph.insert_edge(2, 4, 1);
    graph.insert_edge(3, 4, 4);
    graph.finalize();

    auto path = graph.getShortestPath(0, 3);
    printPath(path);
    // end test



    return 0;
}
