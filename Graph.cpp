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
        if (*(v->first) == label) { 
            //BEFORE WE CALL .ERASE WE SHOULD CALL REMOVE EDGE FOR ALL THE EDGES OF THIS BC THAT
            // WILL JUST CALL DELETE FOR ALL THE EDGES THAT WAS CONNECTED TO THE VERTEX
            for (auto e : (v->second)) { //calling this for every edge at the vertex
                removeEdge(e.get_endpoint1(), e.get_endpoint2());
            }
            adjacency_list.erase(v);
            std::cout << "just erased the vertex" << std::endl;
            break; //found the vertex and erased everything, can break the loop the job is finished
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
    int i = 0; // just for debugging purposes
    for (auto v = adjacency_list.begin(); v != adjacency_list.end(); v++) {
        std::cout << ++i << " time in the first loop." << std::endl;
        if ((*(v->first) == label1) || (*(v->first) == label2)) {
            std::cout << "found the vertex" << std::endl;
            for (auto e = (v->second).begin(); e != (v->second).end(); e++) {
                std::cout << "vertex = " << *(v->first) << std::endl;
                std::cout << "endpoint1 = " << e->get_endpoint1() << std::endl;
                std::cout << "label1 = " << label1 << std::endl;
                std::cout << "endpoint2 = " << e->get_endpoint2() << std::endl;
                std::cout << "label2 = " << label2 << std::endl;
                bool e1 = e->get_endpoint1() == label1;
                std::cout << "e1 = " << e1 << std::endl;
                if (((e->get_endpoint1() == label1) || (e->get_endpoint1() == label2)) ||
                    ((e->get_endpoint2() == label1) || (e->get_endpoint2() == label2))) { // if the vertex appears at all 
                        std::cout << "inside this stupid fucking if statement" << std::endl;
                        (v->second).erase(e); //remove it
                        // removed the edge
                        break; // finished with this
                }
                // if (((e->get_endpoint1() == label1) && (e->get_endpoint2() == label2)) || 
                //     ((e->get_endpoint1() == label2 && (e->get_endpoint2() == label1)))) {
                //         std::cout << "inside inner most if and about to erase" << std::endl;
                //         (v->second).erase(e);
                //         std::cout << "just erased the edge" << std::endl;
                //         break; // break out of this for loop and go to the next vertex to check
                //     }
            }
        }
        std::cout << "at end of first loop" << std::endl;
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