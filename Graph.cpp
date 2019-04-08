#include "Graph.hpp"

bool Edge::operator==(const Edge& rhs) {
    return ((this->get_endpoint1() == rhs.get_endpoint1())
        && (this->get_endpoint2() == rhs.get_endpoint2()));

}
void Graph::addVertex(std::string label) {
    Vertex v{label};
    vertices.push_back(v);
}

void Graph::removeVertex(std::string label) { 
    unsigned int index = 0;
    for (auto iter = vertices.begin(); iter != vertices.end(); iter++) {
        index++;
        if (*(*iter) == label) { //if value at the iterator is equal to the label as arg
            vertices.erase(iter);
            break;
        }
    }
    index -= 1; // decrementing index by 1 to match actual index of vertex

    // erasing the vertex from the adjacency list
    auto element_to_erase = adjacency_list.begin() + index;
    adjacency_list.erase(element_to_erase);

    for (auto list : adjacency_list) {
        for (auto edge : list) {
            // removes the edge containing the vertex that was removeod
            if ((edge.get_endpoint1() == label) || (edge.get_endpoint2() == label)) {
                list.remove(edge);
            }
        }
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    Edge e{label1, label2, weight};

    std::list<Edge> tempList;
    tempList.push_back(e);
    adjacency_list.push_back(tempList);
    // have to sort the adjacency_list to reflect the indexes of the vertices vector

    // if (adjacency_list.empty()) {
    //     std::list<Edge> temp;
    //     temp.push_back(e);
    //     adjacency_list.push_back(temp);
    // }

    // for (unsigned int i = 0; i < vertices.size(); i++) {
    //     auto v = vertices.at(i);
    //     if (*v == label1) {
    //         // accessing an element that does not exist in adjacency_list
    //         adjacency_list.at(i).push_back(e);
    //         break;
    //     }
    // }
    
}

void Graph::removeEdge(std::string label1, std::string label2) {
    for (auto list : adjacency_list) {
        for (auto edge : list) {
            if ((edge.get_endpoint1() == label1) && (edge.get_endpoint2() == label2)) {
                list.remove(edge);
                break;
            }
        }
    }
}

//Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {

}