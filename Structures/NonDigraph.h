#pragma once
#include <iostream>
#include <vector>
#include <climits>
#include <stack>
#include <queue>
#include <algorithm>
#include <iomanip>
#include "Graph.h"

class NonDiGraph : public Graph {
public:
    void addVertex(const std::string& name) override {
        vertices.push_back(new Vertex(name));
    }

    void addEdge(const std::string& fromName, const std::string& toName, double weight) override {
        Vertex* from = findVertex(fromName);
        Vertex* to = findVertex(toName);

        if (from && to) {
            Edge* edge1 = new Edge(from, to, weight);
            Edge* edge2 = new Edge(to, from, weight);
            edges.push_back(edge1);
            edges.push_back(edge2);
            from->addOutEdge(edge1);
            from->addInEdge(edge2);
            to->addOutEdge(edge2);
            to->addInEdge(edge1);
        }
    }

    void findMinimumSpanningTree(std::vector<std::pair<std::string, std::string>>& resultEdges, std::vector<double>& weights) override {
        if (vertices.empty()) return;

        std::vector<bool> visited(vertices.size(), false);
        std::vector<double> minWeight(vertices.size(), std::numeric_limits<double>::infinity());
        std::vector<int> parent(vertices.size(), -1);

        minWeight[0] = 0;

        for (size_t i = 0; i < vertices.size(); ++i) {
            int minVertex = -1;
            for (size_t j = 0; j < vertices.size(); ++j) {
                if (!visited[j] && (minVertex == -1 || minWeight[j] < minWeight[minVertex])) {
                    minVertex = j;
                }
            }

            if (minVertex == -1) break;
            visited[minVertex] = true;

            for (Edge* edge : vertices[minVertex]->getOutEdges()) {
                size_t toIndex = findVertexIndex(edge->getEnd()->getName());
                if (!visited[toIndex] && edge->getWeight() < minWeight[toIndex]) {
                    parent[toIndex] = minVertex;
                    minWeight[toIndex] = edge->getWeight();
                }
            }
        }

        for (size_t i = 1; i < vertices.size(); ++i) {
            if (parent[i] != -1) {
                resultEdges.emplace_back(vertices[parent[i]]->getName(), vertices[i]->getName());
                weights.push_back(minWeight[i]);
            }
        }

        std::cout << "Minimum spanning tree:" << std::endl;
        for (size_t i = 1; i < vertices.size(); ++i) {
            if (parent[i] != -1) {
                std::cout << "Edge: " << vertices[parent[i]]->getName()
                          << " - " << vertices[i]->getName()
                          << " Weight: " << minWeight[i] << std::endl;
            }
        }
    }

    void findShortestPaths(const std::string& startName, std::vector<double>& distances) override{
        Vertex* start = findVertex(startName);
        if (!start) return;

        distances.assign(vertices.size(), std::numeric_limits<double>::infinity());
        size_t startIndex = findVertexIndex(startName);
        distances[startIndex] = 0;

        std::priority_queue<std::pair<double, Vertex*>, std::vector<std::pair<double, Vertex*>>,std::greater<std::pair<double, Vertex*>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            Vertex* current = pq.top().second;
            double currentDist = pq.top().first;
            pq.pop();

            size_t currentIndex = findVertexIndex(current->getName());
            if (currentDist > distances[currentIndex]) continue;

            for (Edge* edge : current->getOutEdges()) {
                size_t toIndex = findVertexIndex(edge->getEnd()->getName());
                if (distances[currentIndex] + edge->getWeight() < distances[toIndex]) {
                    distances[toIndex] = distances[currentIndex] + edge->getWeight();
                    pq.push({distances[toIndex], edge->getEnd()});
                }
            }
        }
        std::cout << "Shortest paths from " << startName << ":" << std::endl;
        for (size_t i = 0; i < vertices.size(); ++i) {
            std::cout << "To " << vertices[i]->getName() << ": ";
            if (distances[i] == std::numeric_limits<double>::infinity()) {
                std::cout << "No path" << std::endl;
            } else {
                std::cout << distances[i] << std::endl;
            }
        }
    }

    void findStronglyConnectedComponents(std::vector<std::vector<std::string>>& components) override {
        std::vector<bool> visited(vertices.size(), false);
        int componentCount = 0;

        std::cout << "Connected Components:" << std::endl;
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (!visited[i]) {
                componentCount++;
                std::cout << "Component " << componentCount << ": ";
                std::vector<std::string> component;
                DFSCollect(vertices[i]->getName(), visited, component);
                std::cout << std::endl;
                components.push_back(component);
            }
        }
    }

    void printGraphVisual() override {
        std::cout << "\nAdjacency Matrix:" << std::endl;
        std::cout << "  ";
        for (auto vertex : vertices) {
            std::cout << std::setw(6) << vertex->getName() << " ";
        }
        std::cout << std::endl;

        for (size_t i = 0; i < vertices.size(); ++i) {
            std::cout << vertices[i]->getName() << " ";
            for (size_t j = 0; j < vertices.size(); ++j) {
                bool hasEdge = false;
                double weight = 0;
                for (Edge* edge : vertices[i]->getOutEdges()) {
                    if (edge->getEnd() == vertices[j]) {
                        hasEdge = true;
                        weight = edge->getWeight();
                        break;
                    }
                }
                if (hasEdge) {
                    std::cout << std::fixed << std::setprecision(0) << std::setw(6) << weight << " ";
                } else {
                    std::cout << std::setw(6) << "0" << " ";
                }

            }
            std::cout << std::endl;
        }

        std::cout << "\nAdjacency List:" << std::endl;
        for (auto vertex : vertices) {
            std::cout << vertex->getName() << " -> ";
            for (Edge* edge : vertex->getOutEdges()) {
                std::cout << edge->getEnd()->getName()
                          << "(" << edge->getWeight() << ") ";
            }
            std::cout << std::endl;
        }
    }

    int getVertexCount() const override{
        return vertices.size();
    }

    int getEdgesCount() const override{
        return edges.size() / 2;
    }

protected:

    void DFSCollect(const std::string& startName, std::vector<bool>& visited, std::vector<std::string>& component) override{
        Vertex* vertex = findVertex(startName);
        if (!vertex) return;

        size_t vertexIndex = findVertexIndex(startName);
        visited[vertexIndex] = true;
        component.push_back(startName);
        std::cout << startName << " ";

        for (Edge* edge : vertex->getOutEdges()) {
            size_t neighborIndex = findVertexIndex(edge->getEnd()->getName());
            if (!visited[neighborIndex]) {
                DFSCollect(edge->getEnd()->getName(), visited, component);
            }
        }
    }

};