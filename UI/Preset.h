#pragma once
#include "../Structures/Digraph.h"
#include "../Structures/NonDigraph.h"

void presets_directed_graph();
void presets_non_directed_graph();
void presets() {
    int var_prog = 0;
    print_choose_struct();
    handlerInput(&var_prog, 1, 2);
    if (var_prog == 1)
        presets_directed_graph();
    else
        presets_non_directed_graph();
}

void presets_directed_graph() {
    DirectedGraph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");

    graph.addEdge("A", "B", 4);
    graph.addEdge("B", "C", 3);
    graph.addEdge("C", "A", 2);
    graph.addEdge("D", "E", 5);
    graph.addEdge("A", "E", 7);
    graph.addEdge("B", "D", 1);
    graph.addEdge("E", "D", 4);

    graph.printGraphVisual();

    std::vector<std::pair<std::string, std::string>> mstEdges;
    std::vector<double> mstWeights;
    graph.findMinimumSpanningTree(mstEdges, mstWeights);

    std::vector<double> shortestPaths;
    graph.findShortestPaths("A", shortestPaths);

    std::vector<std::vector<std::string>> components;
    graph.findStronglyConnectedComponents(components);
}

void presets_non_directed_graph() {
    NonDiGraph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");

    graph.addEdge("A", "B", 2);
    graph.addEdge("B", "C", 3);
    graph.addEdge("C", "D", 1);
    graph.addEdge("D", "E", 4);
    graph.addEdge("E", "A", 5);

    graph.printGraphVisual();

    std::vector<std::pair<std::string, std::string>> mstEdges;
    std::vector<double> mstWeights;
    graph.findMinimumSpanningTree(mstEdges, mstWeights);

    std::vector<double> shortestPaths;
    graph.findShortestPaths("A", shortestPaths);

    std::vector<std::vector<std::string>> components;
    graph.findStronglyConnectedComponents(components);
}
