#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "Graph.hpp"

struct dRow {
    Vertex v;
    unsigned long distance_from_start;
    Vertex prev;
    bool visited = false;
};

class Dijkstra {
public:
    Dijkstra(std::vector<Vertex> verticies) { unvisited = verticies; }
    ~Dijkstra() = default;
    void createTable();
    unsigned long getShortestPath(std::string v1, std::string v2, std::vector<std::string> &path);

private:
    std::vector<Vertex> unvisited;
    std::vector<Vertex> vistied;
    std::vector<dRow> table;
};

#endif