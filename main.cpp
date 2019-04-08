#include "Graph.hpp"
#include <iostream>

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

    auto vertexV = g.get_vertices();
    auto adjl = g.get_adjacency_list();

    std::cout << "VERTEXES ARE: " << std::endl;
    for (auto v : vertexV) {
        std::cout << *v << std::endl;
    }

    std::cout << "Edges are: " << std::endl;
    for (auto l :adjl) {
        for (auto e : l) {
            std::cout << "endpoint 1 = " << e.get_endpoint1() << " endpont 2 = " << 
                e.get_endpoint2() << " weight = " << e.get_weight() << std::endl;
        }
    }

    return 0;
}