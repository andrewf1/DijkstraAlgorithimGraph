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
    std::cout << "----------------------------------------------------------------" << std::endl;

    std::cout << "about to enter main while loop" << std::endl;
    while (!unvisited.empty()) {
        dRow* current_vertex = new dRow;
        current_vertex = &table.at(0);
        std::cout << "current vertex = " << *(current_vertex->v) << std::endl;
        //finding the vertex with smallest distance to make the currentVertex
        for (unsigned int i = 0; i < table.size(); i++) {
            std::cout << i << " time in for loop" << std::endl;
            std::cout << "is this one visited? " << table.at(i).visited << std::endl;
            if(table.at(i).visited != true) {
                std::cout << "it was unvisited" << std::endl;
                dRow* tempVertex = new dRow;
                *tempVertex = table.at(i);
                std::cout << "tempVertex = " << *(tempVertex->v) << std::endl;
                std::cout << "tempVertex->distance = " << tempVertex->distance_from_start << " and currentVertex->distance = " << current_vertex->distance_from_start << std::endl;
                if (current_vertex->visited == true) {
                    std::cout << "the currentVertex was visited" << std::endl;
                    current_vertex = tempVertex;
                    std::cout << "currentVertex now = " << *(current_vertex->v) << std::endl;
                }
                else if (tempVertex->distance_from_start < current_vertex->distance_from_start) {
                    std::cout << tempVertex->distance_from_start << " < " << current_vertex->distance_from_start << std::endl;
                    current_vertex = tempVertex;
                    std::cout << "currentVertex now = " << *(current_vertex->v) << std::endl;
                }
                delete tempVertex;
            }
        }
        std::cout << "-------------------------------------------------" << std::endl;
        // checking all the currentVertex's neighbors to properly updated the shortest distance if applicable
        std::cout << "about to check all the neighbors of the current_vertex" << std::endl;
        auto edge_list = current_vertex->v.get_edge_list();
        int n =0;
        while (!edge_list.empty()) {
            std:: cout << n++ << " time in outter edge_list for loop" << std::endl;
            for (unsigned int i = 0; i < table.size(); i++) {
                std::cout << i << " time in inner table loop" << std::endl;
                std::cout << "edge endpoint = " << edge_list.front()->get_weight() << " and table label = " << *table.at(i).v << std::endl;
                if (edge_list.front()->get_endpoint() == *table.at(i).v) {
                    std::cout  << "\tThey were equal" << std::endl;
                    std::cout << "is the neighbor visited? " << table.at(i).visited << std::endl;
                    if (table.at(i).visited == false) {
                        std::cout << "\tit was not visited" << std::endl;
                        std::cout << "new_dist = " << current_vertex->distance_from_start << " + " << edge_list.front()->get_weight() << std::endl;
                        unsigned long new_distance = current_vertex->distance_from_start + edge_list.front()->get_weight();
                        std::cout << "new_distance = " << new_distance << std::endl;
                        std::cout << "current neighbor's distance = " << table.at(i).distance_from_start << std::endl;
                        if (new_distance < table.at(i).distance_from_start) {
                            table.at(i).distance_from_start = new_distance;
                            table.at(i).prev = current_vertex->v;
                            std::cout << "set the current neighbor's distance from start to the new distance and set its prev vertex to the current vertex" << std::endl;
                        }
                    }
                }
                std::cout << "removing the first element of the list" << std::endl;
                edge_list.pop_front();
            }
        }
        std::cout << "--------------------------------------------------------------------" << std::endl;
        //adding the current_vertex to the list of visited verticies
        std::cout << "pushing " << *current_vertex->v << " back to visited" << std::endl; 
        vistied.push_back(current_vertex->v);
        current_vertex->visited = true;
        std::cout << "set the current_vertex = true" << std::endl;

        // chekcing which vertex to erase from unvisited
        for (unsigned int i = 0; i < unvisited.size(); i++) {
            std::cout << i << " time in deletion for loop" << std::endl;
            std::cout << "unvisited.at(i) = " << *unvisited.at(i) << " and current_vertex = " << *(current_vertex->v) << std::endl;
            if (*unvisited.at(i) == *(current_vertex->v)) {
                auto iter_to_erase = unvisited.begin() + i;
                std::cout << "about to erase: " << *(*iter_to_erase) << std::endl;
                unvisited.erase(iter_to_erase);
                break;
            }
        }
        delete current_vertex;
        std::cout << "just deleted current_vertex" << std::endl;
    }
}

unsigned long Dijkstra::getShortestPath(std::string v1, std::string v2, std::vector<std::string> &path) {
    return 0;
}