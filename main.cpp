#include "Graph.hpp"
#include <iostream>

void printEdges(std::list<Edge*> el) {
    for (auto e : el) {
        std::cout << '[' << e->get_endpoint() << ", " << "(" << e->get_weight() << ")]->";
    }
    std::cout << "[/]" << std::endl;
}

void printGraph(std::vector<Vertex> adjl) {
    for (auto v :adjl) {
        std::cout << "Vertex " << *v << ": ";
        auto elist = v.get_edge_list();
        printEdges(elist);
    }
    // for (auto v : adjl) {
    //     std::cout << "Vertex " << *(v.first) << ": ";
    //     for (auto e : v.second) {
    //         std::cout << '[' << e.get_endpoint1() << ", " << e.get_endpoint2() << " (" << e.get_weight() 
    //         << ")]->";
    //     }
    //     std::cout << "[/]" << std::endl;
    // }
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

    // auto adjl = g.get_adjacency_list();
    // printGraph(adjl);
    // std::cout << std::endl;
    // g.removeVertex("1");
    // adjl = g.get_adjacency_list();
    // printGraph(adjl);
    // std::cout << std::endl;
    // g.removeEdge("1", "2");
    // g.removeEdge("6", "1");
    // g.removeEdge("2", "4");
    // adjl = g.get_adjacency_list();
    // printGraph(adjl);

    std::vector<std::string> path;
    if(g.shortestPath("3", "6", path) == 2) {
        std::cout << "did something right" << std::endl;
    }

    if (g.shortestPath("1", "5", path) == 20) {
        std::cout << "did another something right" << std::endl;
    }

    return 0;
}