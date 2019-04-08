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
    std::cout << "entered remove vertex" << std::endl;
    for (auto v = adjacency_list.begin(); v != adjacency_list.end(); v++) {
        if (*(v->first) == label) { // erase the entire vertex and its edges in the adjacency list
            //BEFORE WE CALL .ERASE WE SHOULD CALL REMOVE EDGE FOR ALL THE EDGES OF THIS BC THAT
            // WILL JUST CALL DELETE FOR ALL THE EDGES THAT WAS CONNECTED TO THE VERTEX
            for (auto e : (v->second)) {
                removeEdge(e.get_endpoint1(), e.get_endpoint2());
            }
            adjacency_list.erase(v);
            std::cout << "just erased the vertex" << std::endl;
        }
        // else { // erase the vertex every time it appears as an endpoint for every other vertex
        //     for (auto e = (v->second).begin(); e != (v->second).end(); e++) {
        //         if ((e->get_endpoint2() == label) || (e->get_endpoint1() == label))  {
        //             std::cout << "about to erase the edge that includes the removed vertex" << std::endl;
        //             removeEdge(e->get_endpoint1(), e->get_endpoint2());
        //             // (v->second).erase(e);
        //             // std::cout << "just erased it";
        //             // break;
        //         }
        //     }
        // }
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    Edge e{label1, label2, weight};

    for (auto v = adjacency_list.begin(); v != adjacency_list.end(); v++) {
        if ((*(v->first) == label1) || (*(v->first) == label2)) {
            (v->second).push_back(e);
        }
    }

    // for (auto v : adjacency_list) { WHY DOES THIS NOT WORK111111111111111111111111
    //     if ((*(v.first) == label1) || (*(v.first) == label2)) {
    //         (v.second).push_back(e);
    //     }
    // }
}

void Graph::removeEdge(std::string label1, std::string label2) {
    std::cout << "inside remove edge" << std::endl;
    for (auto v = adjacency_list.begin(); v != adjacency_list.end(); v++) {
        if ((*(v->first) == label1) || (*(v->first) == label2)) {
            std::cout << "found the vertex" << std::endl;
            for (auto e = (v->second).begin(); e != (v->second).end(); e++) {
                if (((e->get_endpoint1() == label1) && (e->get_endpoint2() == label2))
                    || ((e->get_endpoint1() == label2 && (e->get_endpoint2() == label1)))) {
                        std::cout << "inside inner most if and about to erase" << std::endl;
                        (v->second).erase(e);
                        std::cout << "just erased the edge" << std::endl;
                        break;
                    }
            }
        }
    }
    // for (auto v = adjacency_list.begin(); v != adjacency_list.end(); v++) {
    //     if (*(v->first) == label1) {
    //         for (auto e = (v->second).begin(); e != (v->second).end(); v++) {
    //             if (e->get_endpoint2() == label2) {
    //                 (v->second).erase(e);
    //                 break;
    //             }
    //         }
    //     }
    //     else if (*(v->first) == label2) {
    //         for (auto e = (v->second).begin(); e != (v->second).end(); v++) {
    //             if (e->get_endpoint1() == label1) {
    //                 (v->second).erase(e);
    //                 break;
    //             }
    //         }
    //     }
    // }
}

//Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    return 0;
}