#include "Graph.hpp"
#include <iostream>

void printGraph(std::vector<std::pair<Vertex, std::list<Edge>>> adjl) {
    for (auto v : adjl) {
        std::cout << "Vertex " << *(v.first) << ": ";
        for (auto e : v.second) {
            std::cout << '[' << e.get_endpoint1() << ", " << e.get_endpoint2() << " (" << e.get_weight() 
            << ")]->";
        }
        std::cout << "[/]" << std::endl;
    }
}

int main() {
    struct EdgeStruct { std::string a; std::string b; unsigned long w; };

    Graph g;

    std::vector<std::string> vertices1 { "1", "2", "3", "4", "5", "6" };
    std::vector<EdgeStruct> edges1 {
        {"1", "2", 7}, {"1", "3", 9}, {"1", "6", 14}, {"2", "3", 10}, {"2", "4", 15}, {"3", "4", 11},
        {"3", "6", 2}, {"4", "5", 6}, {"5", "6", 9},
    };

    for (const auto label : vertices1) g.addVertex(label);
    for (const auto &e : edges1) g.addEdge(e.a, e.b, e.w);

    std::cout << "called all addVertex and addEdge" << std::endl;

    auto adjl = g.get_adjacency_list();
    printGraph(adjl);


    g.removeVertex("1");
    std::cout << "removed a vertex" << std::endl;
    adjl = g.get_adjacency_list();
    printGraph(adjl);

    return 0;
}