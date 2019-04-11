#include "GraphBase.hpp"
#include <list>
#include <iostream>

class Edge { // just o0ne endpoint
public:
    Edge(std::string label1, unsigned long _weight) :
        endpoint{label1}, weight{_weight} {}
    // bool operator==(const Edge& lhs);
    std::string get_endpoint() const { return endpoint; }
    // std::string get_endpoint2() const { return endpoint2; }
    unsigned long get_weight() const { return weight; }
private:
    std::string endpoint/*1*/;
    // std::string endpoint2;
    unsigned long weight;
};

class Vertex {
public:
    Vertex(std::string held = "") : data{held} {};
    std::string operator*() { return data; }; //return element at vertex
    bool isAdjacentTo(Vertex v);
private:
    std::string data;
    std::vector<Edge*> edge_list;
};

class Graph : public GraphBase {
public:
    //change these later
    Graph() = default;
    ~Graph() = default;

    int size() { return adjacency_list.size(); } // number of verticies in graph

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