#pragma once
#include "../Structures/Digraph.h"
#include <iostream>

template <typename T>
bool test_directed_graph_add_vertex() {
    DirectedGraph graph;

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");

    std::cout << "test_directed_graph_add_vertex";
    if (graph.getVertexCount() == 3){
        std::cout << "Test passed!" << std::endl;
        return true;
    }else {
        std::cout << "Test failed!" << std::endl;
        return false;
    }
}

template <typename T>
bool test_directed_graph_add_edge() {
    DirectedGraph graph;
    graph.addVertex("A");
    graph.addVertex("B");

    graph.addEdge("A", "B", 5.0);
    graph.addEdge("B", "A", 7.0);

    std::cout << "test_directed_graph_add_edge";
    if (graph.getEdgesCount() == 2){
        std::cout << "Test passed!" << std::endl;
        return true;
    }else {
        std::cout << "Test failed!" << std::endl;
        return false;
    }
}

template <typename T>
bool test_directed_graph_find_minimum_spanning_tree() {
    DirectedGraph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addEdge("A", "B", 1.0);
    graph.addEdge("B", "C", 2.0);
    graph.addEdge("A", "C", 3.0);

    std::vector<std::pair<std::string, std::string>> resultEdges;
    std::vector<double> weights;

    graph.findMinimumSpanningTree(resultEdges, weights);

    std::vector<std::pair<std::string, std::string>> expectedEdges = {{"A", "B"}, {"B", "C"}};
    std::vector<double> expectedWeights = {1.0, 2.0};

    std::cout << "test_directed_graph_find_minimum_spanning_tree";
    if (resultEdges == expectedEdges && weights == expectedWeights){
        std::cout << "Test passed!" << std::endl;
        return true;
    }else {
        std::cout << "Test failed!" << std::endl;
        return false;
    }
}

template <typename T>
bool test_directed_graph_find_shortest_paths() {
    DirectedGraph graph;

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addEdge("A", "B", 1.0);
    graph.addEdge("B", "C", 2.0);
    graph.addEdge("A", "C", 3.0);

    std::vector<double> distances;

    graph.findShortestPaths("A", distances);

    std::vector<double> expectedDistances = {0.0, 1.0, 3.0};

    std::cout << "test_directed_graph_find_shortest_paths: ";
    if (distances == expectedDistances) {
        std::cout << "Test passed!" << std::endl;
        return true;
    } else {
        std::cout << "Test failed!" << std::endl;
        return false;
    }
}


template <typename T>
bool test_directed_graph_find_scc() {
    DirectedGraph graph;

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");
    graph.addEdge("A", "B", 1.0);
    graph.addEdge("B", "C", 1.0);
    graph.addEdge("C", "A", 1.0);
    graph.addEdge("B", "D", 1.0);
    graph.addEdge("D", "E", 1.0);

    std::vector<std::vector<std::string>> components;

    graph.findStronglyConnectedComponents(components);

    std::vector<std::vector<std::string>> expectedComponents = {
            {"E"},
            {"D"},
            {"A", "C", "B"}
    };

    auto sortComponents = [](std::vector<std::vector<std::string>>& comps) {
        for (auto& comp : comps) {
            std::sort(comp.begin(), comp.end());
        }
        std::sort(comps.begin(), comps.end());
    };
    sortComponents(components);
    sortComponents(expectedComponents);

    std::cout << "test_directed_graph_find_scc: ";
    if (components == expectedComponents) {
        std::cout << "Test passed!" << std::endl;
        return true;
    } else {
        std::cout << "Test failed!" << std::endl;
        return false;
    }
}

void test_directed_graph() {
    int total_tests = 5;
    int passed_tests = test_directed_graph_add_vertex<int>() +
                       test_directed_graph_add_edge<int>() +
                       test_directed_graph_find_minimum_spanning_tree<int>() +
                       test_directed_graph_find_shortest_paths<int>() +
                       test_directed_graph_find_scc<int>();

    int failed_tests = total_tests - passed_tests;
    std::cout << "_____________________________________________________________\n";
    std::cout << "Total DirectedGraph tests: " << total_tests << ", Passed: " << passed_tests << ", Failed: " << failed_tests << std::endl;
    std::cout << "_____________________________________________________________\n";
}
