#include "Graph.hpp"
#include "Dijkstra.hpp"

//Graph Destructor
Graph::~Graph() {
    for(unsigned int i = 0; i < adjacency_list.size(); i++) {
        for (auto edge : adjacency_list.at(i).get_edge_list()){
            // delete every edge for every vertex in the graph
            delete edge;
        }
    }
    // clear the adjacency_list for good measure
    adjacency_list.clear();
}

void Graph::addVertex(std::string label) {
    //create vertex object and push back to adjacency list
    Vertex v{label}; 
    adjacency_list.push_back(v);
}

void Graph::removeVertex(std::string label) {
    unsigned int i = 0;
    while (i < adjacency_list.size()) {
        if (*adjacency_list.at(i) == label) { // if found the label of the vertex to remove
            auto pos_to_delete = adjacency_list.begin() + i; //get iterator to remove
            adjacency_list.erase(pos_to_delete); //erase the element at the iterator
        }
        else { // the label is not equal to the vertex the loop is at
            auto elist = adjacency_list.at(i).get_edge_list();
            for (auto e = elist.begin(); e != elist.end(); e++) { // for every edge in the vertex
                auto edge = *e;
                if(edge->get_endpoint() == label) { // delete all occurrances of the label of the vertex to remove
                    adjacency_list.at(i).remove_edge(edge);
                }
            }
            i++; //increment i
        }
    }
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    // create 2 new Edge pointer objects for each combo of the labels given having the same weight
    Edge* vertex_edge = new Edge(label2, weight);
    Edge* endpoint_edge = new Edge(label1, weight);
    //for every vertex in the graph
    for (unsigned int i = 0; i < adjacency_list.size(); i++) {
        if (*adjacency_list.at(i) == label1) { // if the vertex is the first label
            //push back the appropriate edge
            adjacency_list.at(i).push_back_edge(vertex_edge); 
        }
        else if (*adjacency_list.at(i) == label2) { // if the vertex is the second label
            // push back the appropriate edge
            adjacency_list.at(i).push_back_edge(endpoint_edge);
        }
    }
}

void Graph::removeEdge(std::string label1, std::string label2) {
    // for every vertex in the graph
    for (unsigned int i = 0; i < adjacency_list.size(); i++) {
        auto elist = adjacency_list.at(i).get_edge_list();
        auto e = elist.begin();
        while (e != elist.end()) { // for every edge of the vertex
            auto edge = *e;
            if(*adjacency_list.at(i) == label1) { 
                if (edge->get_endpoint() == label2) {
                    // found the appropiate edge and can remove
                    adjacency_list.at(i).remove_edge(edge);
                    break;
                }
            }
            else if (*adjacency_list.at(i) == label2) {
                if (edge->get_endpoint() == label1) {
                    //found edge and remove
                    adjacency_list.at(i).remove_edge(edge);
                    break;
                }
            }
            e++; //incrementing the iterator     
        }
    }
}

// utility function to get the Vertex object given a string
Vertex Graph::at(std::string label)  {
    for (unsigned int i = 0; i < adjacency_list.size(); i++) {
        if (*adjacency_list.at(i) == label) {
            return adjacency_list.at(i);
        }
    }
    Vertex v; // return an empty object if could not find 
    return v;
}

//  utility function called recursivley to complete the path
void createPath(std::vector<std::string>& path, std::map<std::string, std::string> previous, std::string endLabel) {
    if (previous[endLabel] != "") { //if it is not the empty string
        createPath(path, previous, previous[endLabel]); // recursive call
        path.push_back(endLabel);
    }
    else { //return void when the endLabel = ""
        return;
    }
}

//Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    //data structures to implement the algorithm
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> pq;
    std::map<std::string, int> distance_from_start;
    std::map<std::string, std::string> previous;

    //for each vertex in the graph
    for (unsigned int i = 0; i < adjacency_list.size(); i++) {
        // add them to each map with default values
        distance_from_start[*adjacency_list.at(i)] = INT_MAX;
        previous[*adjacency_list.at(i)] = "";
    }
    // push the first vertex into the pq
    pq.push(std::make_pair(0, startLabel));
    distance_from_start[startLabel] = 0; //initial distance is just to itself
    do {
        std::string curr_vertex = pq.top().second; // get a current_vertex
        pq.pop(); //pop it from the queue
        std::string neighbor;

        // for each vertex in the graph
        for (unsigned int i = 0; i < adjacency_list.size(); i++) {
            for (auto edge : adjacency_list.at(i).get_edge_list()) { //for each edge at the vertex
                // check if the loop is at the current vertex
                if(!(*adjacency_list.at(i) == curr_vertex)) {
                    if(!(edge->get_endpoint() == curr_vertex)) {
                        continue;
                    }
                    else {
                        // if the endpoint at the edge is the current vertex
                        neighbor = *adjacency_list.at(i);
                    }
                }
                else { // if not the current vertex
                    /// set the edge to be the neighbor
                    neighbor = edge->get_endpoint();
                }
                auto weight = edge->get_weight();
                unsigned long distance_to_neighbor = distance_from_start[neighbor]; 
                unsigned long distance_to_curr_vertex = distance_from_start[curr_vertex];
                if(!(distance_to_neighbor > distance_to_curr_vertex + weight)) {
                    // do nothing if the distance is not greater than the curr_vertex plus the curr edge's weight
                    continue;
                }
                previous[neighbor] = curr_vertex; // set the previous vertex of the neighbor to the curr_vertex
                distance_from_start[neighbor] = distance_from_start[curr_vertex] + weight; //set the new distance
                pq.push(std::make_pair(distance_from_start[neighbor], neighbor)); // push back into queue
            }
        }
    } while (!pq.empty());

    path.push_back(startLabel);
    createPath(path, previous, endLabel); // finish creating path
    return distance_from_start[endLabel]; // return the weight of the entire path (start->endLabel)

}

