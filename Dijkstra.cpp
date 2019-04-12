#include "Dijkstra.hpp"

const unsigned long infinity = 4294967295;

void Dijkstra::createTable() {
    auto startVertex = unvisited.at(0);
    std::cout << "start vertex = " << *startVertex << std::endl;
    for (unsigned int i = 0; i < unvisited.size(); i++) {
        std::cout << "i = " << i << std::endl;
        std::cout << "*unvisited.at(i) = " << *unvisited.at(i) << std::endl;
        if (i == 0) {
            dRow startRow {*unvisited.at(i), 0, Vertex()};
            std::cout << "push back the startRow into the table" << std::endl;
            table.push_back(startRow);
        }
        else {
            dRow row {*unvisited.at(i), infinity, Vertex()};
            std::cout << "push back the row into the table" << std::endl;
            table.push_back(row);
        }
    }

    std::cout << "about to enter main while loop" << std::endl;
    while (!unvisited.empty()) {
        dRow* current_vertex = new dRow;
        current_vertex = &table.at(0);
        std::cout << "current vertex = " << *(current_vertex->v) << std::endl;
        for (unsigned int i = 0; i < table.size(); i++) {
            std::cout << i << "time in for loop" << std::endl;
            std::cout << "is this one visited? " << table.at(i).visited << std::endl;
            if(table.at(i).visited != true) {
                std::cout << "it was unvisited" << std::endl;
                dRow* tempVertex = new dRow;
                *tempVertex = table.at(i);
                std::cout << "tempVertex = " << *(tempVertex->v) << std::endl;
                if (current_vertex->visited == true) {
                    std::cout << "the currentVertex was visited" << std::endl;
                    current_vertex = tempVertex;
                    std::cout << "currentVertex now = " << *(current_vertex->v);
                }
                else if (tempVertex->distance_from_start < current_vertex->distance_from_start) {
                    std::cout << tempVertex->distance_from_start << " < " << current_vertex->distance_from_start << std::endl;
                    current_vertex = tempVertex;
                    std::cout << "currentVertex now = " << *(current_vertex->v);
                }
                delete tempVertex;
            }
        }
        std::cout << "-------------------------------------------------" << std::endl;
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
    return 0;
}