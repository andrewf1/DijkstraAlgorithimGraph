#include "GraphBase.hpp"
#include <list>

class Graph : public GraphBase {
public:
    //change these later
    Graph() : n{0} {}
    ~Graph() = default;

    int size() { return n; } // number of verticies in graph

    virtual void addVertex(std::string label); //inserts a new vertex storing the element
    virtual void removeVertex(std::string label);  // remove vertex containing the element and all its incident edges
    virtual void addEdge(std::string label1, std::string label2, unsigned long weight); //insert a new undirected edge with end vertices
    virtual void removeEdge(std::string label1, std::string label2); // remove the edge between the two vertices given
    virtual unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);

    std::list<Vertex> vertices(); // returns a vertex list of all the vertices of the graph
    std::list<Edge> edges(); //returns an edge list of all the edges of the graph
    
private:
    std::vector<std::vector<Vertex>> adjacency_list;
    int n;
};

class Edge {
public:
    Edge(std::string label1, std::string label2, unsigned long _weight) :
        endpoint1{label1}, endpoint2{label2}, weight{_weight} {}
private:
    std::string endpoint1;
    std::string endpoint2;
    unsigned long weight;
};

class Vertex {
public:
    Vertex(std::string held = "") : data{held} {};
    std::string operator*() { return data; }; //return element at vertex
    bool isAdjacentTo(Vertex v);
private:
    std::string data;
};
