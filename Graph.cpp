#include "Graph.hpp"

void Graph::addVertex(std::string label) {
    Vertex v{label};
    vertices.push_back(v);
}

void removeVertex(std::string label) { 

}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    Edge e{label1, label2, weight};
    
    for (auto i = 0; i < vertices.size(); i++) {
        auto v = vertices.at(i);
        if (*v == label1) {
            adjacency_list.at(i).push_back(e);
            break;
        }
    }
}

void Graph::removeEdge(std::string label1, std::string label2) {

}

//Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {

}