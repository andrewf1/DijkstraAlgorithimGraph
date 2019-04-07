#include "Graph.hpp"

void Graph::addVertex(std::string label) {
    Vertex v{label};
    adjacency_list.push_back.push_back(v);
}

void removeVertex(std::string label) { 

}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    Edge e{label1, label2, weight};
    for (auto vec : adjacency_list) {
        for (auto j : vec) {
            if (*j == label1) {
                vec.push_back(e);
            }
        }
    }
}

void Graph::removeEdge(std::string label1, std::string label2) {

}

//Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {

}