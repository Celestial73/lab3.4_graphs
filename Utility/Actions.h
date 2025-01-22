#pragma once
#include <iostream>
#include "../UI/Menu.h"
#include "Handlers.h"
#include <sstream>
#include "../Structures/Digraph.h"
#include "../Structures/NonDigraph.h"
void digraph_actions();
void non_digraph_actions();
void manualFillGraph(DirectedGraph& graph);
void manualFillNONDIGraph(NonDiGraph& graph);

void program_work() {
    int var_prog = 0;
    print_choose_struct();
    handlerInput(&var_prog, 1, 2);
    if (var_prog == 1)
        digraph_actions();
    else
        non_digraph_actions();
}


void digraph_actions() {
    DirectedGraph graph;
    manualFillGraph(graph);
    int var_action = 0;
    do {
        print_prog_action_graph();
        handlerInput(&var_action, 1, 6);
        if (var_action == 1){
            std::vector<std::pair<std::string, std::string>> resultEdges;
            std::vector<double> weights;
            graph.findMinimumSpanningTree(resultEdges, weights);
        } else if (var_action == 2){
            std::vector<std::vector<std::string>> components;
            graph.findStronglyConnectedComponents(components);
        } else if (var_action == 3){
            std::string startVertex;

            std::cout << "Enter starting vertex: ";
            std::cin >> startVertex;

            std::vector<double> distances;
            graph.findShortestPaths(startVertex, distances);
        } else if (var_action == 4){
            graph.printGraphVisual();
        }
    } while (var_action != 5);
}



void non_digraph_actions() {
    NonDiGraph graph;

    manualFillNONDIGraph(graph);

    int var_action = 0;
    do {
        print_prog_action_graph();
        handlerInput(&var_action, 1, 6);

        if (var_action == 1) {
            std::vector<std::pair<std::string, std::string>> resultEdges;
            std::vector<double> weights;
            graph.findMinimumSpanningTree(resultEdges, weights);
        } else if (var_action == 2) {
            std::vector<std::vector<std::string>> components;
            graph.findStronglyConnectedComponents(components);
        } else if (var_action == 3) {
            std::string startVertex;

            std::cout << "Enter starting vertex: ";
            std::cin >> startVertex;

            std::vector<double> distances;
            graph.findShortestPaths(startVertex, distances);
        } else if (var_action == 4){
            graph.printGraphVisual();
        }
    } while (var_action != 5);
}



void manualFillGraph(DirectedGraph& graph) {
    int numVertices;
    cout << "Enter the number of vertices:";
    cin >> numVertices;

    vector<string> vertexNames;
    for (int i = 0; i < numVertices; ++i) {
        string vertexName;
        cout << "Enter name for vertex " << i << ": ";
        cin >> vertexName;
        vertexNames.push_back(vertexName);
        graph.addVertex(vertexName);
    }

    for (int i = 0; i < numVertices; ++i) {
        cout << "Enter, separated by commas, which vertices the vertex " << vertexNames[i] << " will be associated with:";

        string input;
        getline(cin >> ws, input);

        vector<string> connectedVertices;
        stringstream ss(input);
        string vertex;

        while (getline(ss, vertex, ',')) {
            connectedVertices.push_back(vertex);
        }

        cout << "Enter edge weight:\n";
        for (const string& connectedVertex : connectedVertices) {
            int weight;
            cout << "Edge weight " << vertexNames[i] << " -> " << connectedVertex << ": ";
            cin >> weight;

            graph.addEdge(vertexNames[i], connectedVertex, weight);
        }
    }
}

void manualFillNONDIGraph(NonDiGraph& graph) {
    int numVertices;
    cout << "Enter the number of vertices:";
    cin >> numVertices;

    vector<string> vertexNames;
    for (int i = 0; i < numVertices; ++i) {
        string vertexName;
        cout << "Enter name for vertex " << i << ": ";
        cin >> vertexName;
        vertexNames.push_back(vertexName);
        graph.addVertex(vertexName);
    }

    for (int i = 0; i < numVertices; ++i) {
        cout << "Enter, separated by commas, which vertices the vertex " << vertexNames[i] << " will be associated with:";

        string input;
        getline(cin >> ws, input);

        vector<string> connectedVertices;
        stringstream ss(input);
        string vertex;

        while (getline(ss, vertex, ',')) {
            connectedVertices.push_back(vertex);
        }

        cout << "Enter edge weight:\n";
        for (const string& connectedVertex : connectedVertices) {
            int weight;
            cout << "Edge weight " << vertexNames[i] << " -- " << connectedVertex << ": ";
            cin >> weight;

            graph.addEdge(vertexNames[i], connectedVertex, weight);
        }
    }
}


