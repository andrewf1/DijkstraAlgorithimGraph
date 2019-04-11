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

Vertex Graph::at(std::string label)  {
    for (unsigned int i = 0; i < adjacency_list.size(); i++) {
        if (*adjacency_list.at(i) == label) {
            return adjacency_list.at(i);
        }
    }
    Vertex v;
    return v;
}

bool Graph::checkPath(std::string curr_vertex, std::string destination) {
    if(curr_vertex == destination) {
        return true;
    }
    else {
        auto v = at(curr_vertex);
        for (auto e = v.get_edge_list().begin(); e != v.get_edge_list().end(); e++) {
            checkPath((*e)->get_endpoint(), destination);
        }
        return false;
    }
}

unsigned long Graph::calculate_weight(std::vector<std::string> path, unsigned long curr_weight) {
    unsigned long weight = 0;
    std::vector<std::string> new_path;
    if (path.size() == 2) {
        auto v = at(path.at(0));
        for (auto e = v.get_edge_list().begin(); e != v.get_edge_list().end(); e++) {
            auto edge = *e;
            if (edge->get_endpoint() == path.at(1)) {
                return edge->get_weight() + curr_weight;
            }
        }
        return weight;
    }
    else {
        for (unsigned int i = 0; i < path.size(); i++) {
            auto v = at(path.at(i));
            for(auto e = v.get_edge_list().begin(); e != v.get_edge_list().end(); e++) {
                auto edge = *e;
                if (edge->get_endpoint() == path.at(1)) {
                    weight += edge->get_weight();
                    break;
                }
            }
            if ((i != 0) || (i != 1)) {
                new_path.push_back(path.at(i));
            }
        }
        calculate_weight(new_path, weight);
    }        
}

//     for (unsigned int i = 0; i < path.size(); i++) {
//         auto v = at(path.at(i));
//         if (i != (path.size() - 1)) {
//             for(auto e = v.get_edge_list().begin(); e != v.get_edge_list().end(); e++) {
//                 auto edge = *e;
//                 if (edge->get_endpoint() == path.at(i+1)) {
//                     weight += edge->get_weight();
//                 }
//             }
//         }
//         else {
            
//         }
//     }
// }

//Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    //use recursion
    // auto unvisited = adjacency_list;
    // int distance = 0;
    // while (!unvisited.empty()) {
    //     auto curr_vertex = unvisited.at(0);
    //     for (auto e = curr_vertex.get_edge_list().begin(); e != curr_vertex.get_edge_list().end(); e++) {
    //         auto edge = *e;
    //         int new_dist_from_start = edge->get_weight() + 0;
            
    //     }
    // }

    auto curr_vertex = at(startLabel);
    std::string next_vertex;
    unsigned long distance = 0;
    bool first_time = true;
    for (auto e = curr_vertex.get_edge_list().begin(); e != curr_vertex.get_edge_list().end(); e++) {
        auto edge = *e;
        unsigned long temp_dist = distance + edge->get_weight();
        if (checkPath(*curr_vertex, endLabel)) {
            if (temp_dist < distance || first_time) {
                first_time = false;
                distance = temp_dist;
                next_vertex = edge->get_endpoint();
            }
        }
    }
    if(!next_vertex.empty()) {
        path.push_back(next_vertex);
        return distance + shortestPath(next_vertex, endLabel, path);
    }
    else {
        //cal a function that calculates the weight given the path 
        return calculate_weight(path, distance);
    }
}