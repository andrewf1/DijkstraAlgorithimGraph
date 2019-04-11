#include "Graph.hpp"

void Graph::addVertex(std::string label) {
    Vertex v{label};
    adjacency_list.push_back(v);
}

void Graph::removeVertex(std::string label) {
    unsigned int i = 0;
    while (i < adjacency_list.size()) {
        if (*adjacency_list.at(i) == label) {
            auto pos_to_delete = adjacency_list.begin() + i;
            adjacency_list.erase(pos_to_delete);
        }
        else {
            auto elist = adjacency_list.at(i).get_edge_list();
            for (auto e = elist.begin(); e != elist.end(); e++) {
                auto edge = *e;
                if(edge->get_endpoint() == label) {
                    adjacency_list.at(i).remove_edge(edge);
                }
            }
            i++; //increment i
        }
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    Edge* vertex_edge = new Edge(label2, weight);
    Edge* endpoint_edge = new Edge(label1, weight);
    for (unsigned int i = 0; i < adjacency_list.size(); i++) {
        if (*adjacency_list.at(i) == label1) {
            adjacency_list.at(i).push_back_edge(vertex_edge); 
        }
        else if (*adjacency_list.at(i) == label2) {
            adjacency_list.at(i).push_back_edge(endpoint_edge);
        }
    }
}

void Graph::removeEdge(std::string label1, std::string label2) {
    for (unsigned int i = 0; i < adjacency_list.size(); i++) {
        auto elist = adjacency_list.at(i).get_edge_list();
        auto e = elist.begin();
        while (e != elist.end()) {
            auto edge = *e;
            if(*adjacency_list.at(i) == label1) {
                if (edge->get_endpoint() == label2) {
                    adjacency_list.at(i).remove_edge(edge);
                    break;
                }
            }
            else if (*adjacency_list.at(i) == label2) {
                if (edge->get_endpoint() == label1) {
                    adjacency_list.at(i).remove_edge(edge);
                    break;
                }
            }
            e++; //incrementing the iterator     
        }
    }
}
//Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    //use recursion
    return 0;
}