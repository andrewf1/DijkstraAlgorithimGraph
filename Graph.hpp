#include "GraphBase.hpp"
#include <list>

class Edge {
public:
    Edge(std::string label1, std::string label2, unsigned long _weight) :
        endpoint1{label1}, endpoint2{label2}, weight{_weight} {}
    std::string get_endpoint1() { return endpoint1; }
    std::string get_endpoint2() { return endpoint2; }
    unsigned long get_weight() const { return weight; }
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

class Graph : public GraphBase {
public:
    //change these later
    Graph() = default;
    ~Graph() = default;

    int size() { return vertices.size(); } // number of verticies in graph

    virtual void addVertex(std::string label); //inserts a new vertex storing the element
    virtual void removeVertex(std::string label);  // remove vertex containing the element and all its incident edges
    virtual void addEdge(std::string label1, std::string label2, unsigned long weight); //insert a new undirected edge with end vertices
    virtual void removeEdge(std::string label1, std::string label2); // remove the edge between the two vertices given
    virtual unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);

    std::vector<Vertex> get_vertices() const { return vertices; } // returns a vertex list of all the vertices of the graph
    std::vector<std::list<Edge>> get_adjacency_list() const { return adjacency_list; } //returns an edge list of all the edges of the graph
    
private:
    std::vector<std::list<Edge>> adjacency_list;
    std::vector<Vertex> vertices;
};