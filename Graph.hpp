#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphBase.hpp"
#include <list>
#include <iostream>
#include <tuple>
#include <queue>
#include <limits.h>
#include <map>

class Edge { 
public:
    Edge(std::string label1, unsigned long _weight) :
        endpoint{label1}, weight{_weight} {}
    std::string get_endpoint() const { return endpoint; }
    unsigned long get_weight() const { return weight; }
private:
    std::string endpoint;
    unsigned long weight;
};

class Vertex {
public:
    Vertex(std::string held = "") : data{held} {};
    std::string operator*() { return data; }; //return element at vertex
    void push_back_edge(Edge* e) { edge_list.push_back(e); }
    void remove_edge(Edge* edge) { edge_list.remove(edge); }
    std::list<Edge*> get_edge_list() { return edge_list; }
    bool isAdjacentTo(Vertex v);
private:
    std::string data;
    std::list<Edge*> edge_list;
};

class Graph : public GraphBase {
public:
    //change these later
    Graph() = default;
    ~Graph() = default; //especially this one

    int size() { return adjacency_list.size(); } // number of verticies in graph
    Vertex at(std::string label);
    bool checkPath(std::string curr_vertex, std::string destination);
    unsigned long calculate_weight(std::vector<std::string> path, unsigned long curr_weight);

    virtual void addVertex(std::string label); //inserts a new vertex storing the element
    virtual void removeVertex(std::string label);  // remove vertex containing the element and all its incident edges
    virtual void addEdge(std::string label1, std::string label2, unsigned long weight); //insert a new undirected edge with end vertices
    virtual void removeEdge(std::string label1, std::string label2); // remove the edge between the two vertices given
    virtual unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);

    std::vector<Vertex> get_adjacency_list() const { return adjacency_list; } 
    
private:
    // std::vector<std::pair<Vertex, std::list<Edge>>> adjacency_list;
    std::vector<Vertex> adjacency_list;
};

#endif