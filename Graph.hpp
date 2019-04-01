#include "GraphBase.hpp"

class Graph : public GraphBase {
public:
    //change these later
    Graph() : start{nullptr}, n{0} {};
    ~Graph() = default;

    int size() { return n; }

    virtual void addVertex(std::string label);
    virtual void removeVertex(std::string label);
    virtual void addEdge(std::string label1, std::string label2, unsigned long weight);
    virtual void removeEdge(std::string label1, std::string label2);
    virtual unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
private:
    Vertex* start;
    int n; //number of vertecies in the graph
};

class Edge {
public:

private:
    std::string source_vertex;
    std::string destination_vertex;
};

class Vertex {
public:
    Vertex(std::string held = "") : data{held} {};
    std::string operator*() { return data; };
private:
    std::string data;
};

