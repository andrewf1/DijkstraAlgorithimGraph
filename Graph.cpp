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

//Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> pq;
    std::map<std::string, int> distance_from_start;
    std::map<std::string, std::string> previous;

    for (unsigned int i = 0; i < adjacency_list.size(); i++) {
        distance_from_start[*adjacency_list.at(i)] = INT_MAX;
        previous[*adjacency_list.at(i)] = "";
    }

    pq.push(std::make_pair(0, startLabel));
    distance_from_start[startLabel] = 0;
    do {
        std::string curr_vertex = pq.top().second;
        pq.pop();
        std::string neighbor;

        for (unsigned int i = 0; i < adjacency_list.size(); i++) {
            for (auto edge : adjacency_list.at(i).get_edge_list()) {
                if(!(*adjacency_list.at(i) == curr_vertex)) {
                    if(!(edge->get_endpoint() == curr_vertex)) {
                        continue;
                    }
                    else {
                        neighbor = *adjacency_list.at(i);
                    }
                }
                else {
                    neighbor = edge->get_endpoint();
                }
                auto weight = edge->get_weight();
                if(!(distance_from_start[neighbor] > distance_from_start[curr_vertex] + weight)) {
                    continue;
                }
                previous[neighbor] = curr_vertex;
                distance_from_start[neighbor] = distance_from_start[curr_vertex] + weight;
                pq.push(std::make_pair(distance_from_start[neighbor], neighbor));
            }
        }
    } while (!pq.empty());

    path.push_back(startLabel);
    createPath(path, previous, endLabel);
    return distance_from_start[endLabel];

}

void Graph::createPath(std::vector<std::string>& path, std::map<std::string, std::string> previous, std::string endLabel) {
    if (previous[endLabel] != "") { //if it is not the empty string
        createPath(path, previous, previous[endLabel]);
        path.push_back(endLabel);
    }
    else { //return void when the endLabel = ""
        return;
    }
}

