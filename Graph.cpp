#include "Graph.hpp"
#include "Dijkstra.hpp"

Graph::~Graph() {
    for(unsigned int i = 0; i < adjacency_list.size(); i++) {
        for (auto edge : adjacency_list.at(i).get_edge_list()){
            delete edge;
        }
    }
    adjacency_list.clear();
}

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

// bool Graph::checkPath(std::string curr_vertex, std::string destination) {
//     std::cout << "\tinside checkPath" << std::endl;
//     if(curr_vertex == destination) {
//         std::cout << "\tCheckPath is about to return true" << std::endl;
//         return true;
//     }
//     else {
//         auto v = at(curr_vertex);
//         for (auto e = v.get_edge_list().begin(); e != v.get_edge_list().end(); e++) {
//             std::cout << "\tinside the for loop of checkPath, new endpoint = " << (*e)->get_endpoint() << std::endl;
//             return checkPath((*e)->get_endpoint(), destination);
//         }
//         std::cout << "\tcheckPath is about to return false" << std::endl;
//         return false;
//     }
// }

// unsigned long Graph::calculate_weight(std::vector<std::string> path, unsigned long curr_weight) {
//     unsigned long weight = 0;
//     std::vector<std::string> new_path;
//     if (path.size() == 2) {
//         std::cout << "\tthe path size is 2" << std::endl;
//         std::cout << "\tpath.at(0) = " << path.at(0) << std::endl;
//         auto v = at(path.at(0));
//         for (auto e = v.get_edge_list().begin(); e != v.get_edge_list().end(); e++) {
//             auto edge = *e;
//             std::cout << "\tpath.at(1) = " << path.at(1) << std::endl;
//             if (edge->get_endpoint() == path.at(1)) {
//                 std::cout << "\tinside the if and edge->get_endpoint(() = " << edge->get_endpoint() << std::endl;
//                 return edge->get_weight() + curr_weight;
//             }
//         }
//     }
//     else {
//         std::cout << "\tin the else of calculate weight" << std::endl;
//         int n = 0;
//         for (unsigned int i = 0; i < path.size(); i++) {
//             std::cout << "\t" << ++n << " time in the for loop" << std::endl;
//             auto v = at(path.at(i));
//             for(auto e = v.get_edge_list().begin(); e != v.get_edge_list().end(); e++) {
//                 std::cout << "\t\tinside inner most loop" << std::endl;
//                 auto edge = *e;
//                 std::cout << "\t\tendpoint = " << edge->get_endpoint() << " and path.at(i+1) + " << path.at(i+1) << std::endl;
//                 if (edge->get_endpoint() == path.at(i + 1)) {
//                     weight += edge->get_weight();
//                     std::cout << "\t\tnew weight = " << weight << std::endl;
//                     break;
//                 }
//             }
//             if ((i != 0) || (i != 1)) {
//                 std::cout << "\tpushing back [" << path.at(i) << "]" << std::endl;
//                 new_path.push_back(path.at(i));
//             }
//         }
//         std::cout << "\tabout to recursviely call calculate weight" << std::endl;
//         calculate_weight(new_path, weight);
//     }        
//     return weight;
// }

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

// man scratch this and start over, it is not working, we are getting the smallest weighted edge, not necessarily
//the one that is going to reach the path with least weight eventually (check 1 -> 6)
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    // std::cout << "start vertex = " << startLabel << " and end vertex = " << endLabel << std::endl;
    //use recursion
    // auto unvisited = adjacency_list;
    // int distance_from_start = 0;
    // while (!unvisited.empty()) {
    //     auto curr_vertex = unvisited.at(0);
    //     for (auto e = curr_vertex.get_edge_list().begin(); e != curr_vertex.get_edge_list().end(); e++) {
    //         auto edge = *e;
    //         int new_dist_from_start = edge->get_weight() + 0;
            
    //     }
    // }

    // auto curr_vertex = at(startLabel);
    // std::string next_vertex;
    // unsigned long distance = 0;
    // bool first_time = true;
    //--------------------------------------------------------------------------------------------------
    // int n = 0;
    // for (auto e = curr_vertex.get_edge_list().begin(); e != curr_vertex.get_edge_list().end(); e++) {
    //     // avoid iterators... find a way to get a iterator of a list when have the index
    //     std::cout << ++n << " time in the for loop" << std::endl;
    //     auto edge = *e;
    //     unsigned long temp_dist = distance + edge->get_weight();
    //     std::cout << "distance = " << distance << " and edge->get_weight() = " << edge->get_weight() << std::endl;
    //     if (checkPath(*curr_vertex, endLabel)) {
    //         std::cout << "checkPath returned true" << std::endl;
    //         std::cout << "temp_dist = " << temp_dist << ", distance = " << distance << std::endl;
    //         if (temp_dist < distance || first_time) {
    //             std::cout << "it is the first time running or temp_dist < distance" << std::endl;
    //             first_time = false;
    //             distance = temp_dist;
    //             next_vertex = edge->get_endpoint();
    //             std::cout << "next_vertex is now set to: " << edge->get_endpoint() << std::endl;
    //             if(edge->get_endpoint() == endLabel) {
    //                 return distance;
    //             }
    //         }
    //     }
    // }
    //------------------------------------------------------------------------------------------------




    // auto edge = curr_vertex.get_edge_list().begin();
    // int n = 0;
    // for (unsigned int i = 0; i < curr_vertex.get_edge_list().size(); i++) {
    //     std::cout << "edge->get_weight() = " << (*edge)->get_weight() << std::endl;
    //     std::cout << ++n << " time in the for loop" << std::endl;
    //     if(edge != curr_vertex.get_edge_list().begin() && edge != curr_vertex.get_edge_list().end()) {
    //         edge++;
    //     }
    //     unsigned long temp_dist = distance + (*edge)->get_weight();
    //     std::cout << "distance = " << distance << " and edge->get_weight() = " << (*edge)->get_weight() << std::endl;
    //     std::cout << "curr_vertex = " << *curr_vertex << " and endLabel = " << endLabel << std::endl;
    //     if (checkPath(*curr_vertex, endLabel)) {
    //         std::cout << "checkPath returned true" << std::endl;
    //         std::cout << "temp_dist = " << temp_dist << ", distance = " << distance << std::endl;
    //         if (temp_dist < distance || first_time) {
    //             std::cout << "it is the first time running or temp_dist < distance" << std::endl;
    //             first_time = false;
    //             distance = temp_dist;
    //             next_vertex = (*edge)->get_endpoint();
    //             std::cout << "next_vertex is now set to: " << (*edge)->get_endpoint() << std::endl;
    //         }
    //     }
    // }
    // if(!next_vertex.empty()) {
    //     std::cout << "pushing [" << next_vertex << "] into the path" << std::endl;
    //     path.push_back(next_vertex);
    //     return distance + shortestPath(next_vertex, endLabel, path);
    // }
    // else {
    //     //cal a function that calculates the weight given the path 
    //     std::cout << "about to call calculate weight" << std::endl;
    //     return calculate_weight(path, distance);
    // }

    // Dijkstra algo(adjacency_list);
    // algo.createTable();
    // return 0;
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> pq;
    std::map<std::string, int> distance_from_start;
    std::map<std::string, std::string> previous;

    for (unsigned int i = 0; i < adjacency_list.size(); i++) {
        distance_from_start[*adjacency_list.at(i)] = INT_MAX;
        previous[*adjacency_list.at(i)] = "flag";
    }

    pq.push(std::make_pair(0, startLabel));
    distance_from_start[startLabel] = 0;
    do {
        std::string str1 = pq.top().second;
        pq.pop();
        std::string B;

        for (unsigned int i = 0; i < adjacency_list.size(); i++) {
            for (auto x : adjacency_list.at(i).get_edge_list()) {
                if(!(*adjacency_list.at(i) == str1)) {
                    if(!(x->get_endpoint() == str1)) {
                        continue;
                    }
                    else {
                        B = *adjacency_list.at(i);
                    }
                }
                else {
                    B = x->get_endpoint();
                }
                auto weight = x->get_weight();
                if(!(distance_from_start[B] > distance_from_start[str1] + weight)) {
                    continue;
                }
                previous[B] = str1;
                distance_from_start[B] = distance_from_start[str1] + weight;
                pq.push(std::make_pair(distance_from_start[B], B));
            }
        }
    } while (!pq.empty());

    path.push_back(startLabel);
    createPath(previous, endLabel, path);
    return distance_from_start[endLabel];

}

void Graph::createPath(std::map<std::string, std::string> previous, std::string endLabel , std::vector<std::string> &path) {
    if (previous[endLabel] != "flag"){
        createPath(previous, previous[endLabel],path);
        path.push_back(endLabel);
    }
    else
        return;
}

