#include "Dijkstra.hpp"

const unsigned long infinity = 4294967295;

void Dijkstra::createTable() {
    auto startVertex = unvisited.at(0);
    for (unsigned int i = 0; i < unvisited.size(); i++) {
        if (i == 0) {
            dRow startRow {*unvisited.at(i), 0, Vertex()};
            table.push_back(startRow);
        }
        else {
            dRow row {*unvisited.at(i), infinity, Vertex()};
            table.push_back(row);
        }
    }
    while (!unvisited.empty()) {
        dRow* current_vertex = new dRow;
        current_vertex = &table.at(0);
        for (unsigned int i = 0; i < table.size(); i++) {
            if(table.at(i).visited != true) {
                dRow* tempVertex = new dRow;
                *tempVertex = table.at(i);
                if (tempVertex->distance_from_start < current_vertex->distance_from_start) {
                    current_vertex = tempVertex;
                }
            }
        }
        auto edge_list = current_vertex->v.get_edge_list();
        for (auto edge : edge_list) {
            for (unsigned int i = 0; i < table.size(); i++) {
                if ((*edge).get_endpoint() == *table.at(i).v) {
                    if (table.at(i).visited == false) {
                        unsigned long new_distance = current_vertex->distance_from_start + (*edge).get_weight();
                        if (new_distance < table.at(i).distance_from_start) {
                            table.at(i).distance_from_start = new_distance;
                            table.at(i).prev = current_vertex->v;
                        }
                    }
                }
            }
        }
        
        //adding the current_vertex to the list of visited verticies
        vistied.push_back(current_vertex->v);
        current_vertex->visited = true;
        for (unsigned int i = 0; i < unvisited.size(); i++) {
            if (*unvisited.at(i) == *(current_vertex->v)) {
                auto iter_to_erase = unvisited.begin() + i;
                unvisited.erase(iter_to_erase);
                break;
            }
        }
        delete current_vertex;
    }
}

unsigned long Dijkstra::getShortestPath(std::string v1, std::string v2, std::vector<std::string> &path) {

}