#include "Graph.hpp"

// bool Edge::operator==(const Edge& rhs) {
//     return ((this->get_endpoint1() == rhs.get_endpoint1())
//         && (this->get_endpoint2() == rhs.get_endpoint2()));

// }
void Graph::addVertex(std::string label) {
    Vertex v{label};
    std::list<Edge> emptyList;
    auto p = std::make_pair(v, emptyList);
    adjacency_list.push_back(p);
}

void Graph::removeVertex(std::string label) { 
    for (auto v = adjacency_list.begin(); v != adjacency_list.end(); v++) {
        if (*(v->first) == label) { // erase the entire vertex and its edges in the adjacency list
            adjacency_list.erase(v);
        }
        else { // erase the vertex every time it appears as an endpoint for every other vertex
            for (auto e = (v->second).begin(); e != (v->second).end(); e++) {
                if ((e->get_endpoint2() == label) || (e->get_endpoint1() == label))  {
                    (v->second).erase(e);
                }
            }
        }
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    Edge e{label1, label2, weight};

    for (auto iter = adjacency_list.begin(); iter != adjacency_list.end(); iter++) {
        if (*(iter->first) == label1) {
            (iter->second).push_back(e);
            break;
        }
    }
}

void Graph::removeEdge(std::string label1, std::string label2) {
    for (auto v = adjacency_list.begin(); v != adjacency_list.end(); v++) {
        if (*(v->first) == label1) {
            for (auto e = (v->second).begin(); e != (v->second).end(); v++) {
                if (e->get_endpoint2() == label2) {
                    (v->second).erase(e);
                    break;
                }
            }
        }
    }
}

//Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    return 0;
}