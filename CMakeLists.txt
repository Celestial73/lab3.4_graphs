cmake_minimum_required(VERSION 3.25)
project(lab4_graphs)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        lab4_graphs
        main.cpp
        Utility/Actions.h
        Utility/Handlers.h
        UI/Menu.h
        Tests/Tests.h
        Tests/TestDiGraph.h
        Tests/TestNonDiGraph.h
        Structures/Digraph.h
        Structures/NonDigraph.h
        Structures/Graph.h
        UI/Preset.h)
