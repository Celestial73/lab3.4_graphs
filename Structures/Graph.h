#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <stack>
#include <queue>
#include <algorithm>

struct Edge;

struct Vertex {
private:
    std::string name;
    std::vector<Edge*> inEdges;
    std::vector<Edge*> outEdges;

public:
    explicit Vertex(std::string n) : name(std::move(n)) {}

    void addInEdge(Edge* edge) { inEdges.push_back(edge); }
    void addOutEdge(Edge* edge) { outEdges.push_back(edge); }

    const std::string& getName() const { return name; }
    const std::vector<Edge*>& getInEdges() const { return inEdges; }
    const std::vector<Edge*>& getOutEdges() const { return outEdges; }
};

struct Edge {
private:
    Vertex* startVertex;
    Vertex* endVertex;
    double weight;

public:
    Edge(Vertex* start, Vertex* end, double w)
            : startVertex(start), endVertex(end), weight(w) {}

    Vertex* getStart() const { return startVertex; }
    Vertex* getEnd() const { return endVertex; }
    double getWeight() const { return weight; }
};

class Graph {
protected:
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;

public:
    Graph() = default;
    virtual ~Graph() {
        for (auto vertex : vertices) delete vertex;
        for (auto edge : edges) delete edge;
    }

    virtual void addVertex(const std::string& name) = 0;
    virtual void addEdge(const std::string& fromName, const std::string& toName, double weight) = 0;
    virtual void findMinimumSpanningTree(std::vector<std::pair<std::string, std::string>>& resultEdges, std::vector<double>& weights) = 0;
    virtual void findShortestPaths(const std::string& startName, std::vector<double>& distances) = 0;
    virtual void findStronglyConnectedComponents(std::vector<std::vector<std::string>>& components) = 0;
    virtual void printGraphVisual() = 0;
    virtual int getVertexCount() const = 0;
    virtual int getEdgesCount() const = 0;

protected:
    Vertex* findVertex(const std::string& name) {
        for (Vertex* vertex : vertices) {
            if (vertex->getName() == name) return vertex;
        }
        return nullptr;
    }

    size_t findVertexIndex(const std::string& name) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (vertices[i]->getName() == name) return i;
        }
        return -1;
    }

    virtual void DFSCollect(const std::string& startName, std::vector<bool>& visited, std::vector<std::string>& component) = 0;
};
