#pragma once
#include <iostream>
using namespace std;

void print_choose_prog() {
    cout << "_____________________________________________________________\n";
    cout << "Select the actions:\n" <<
         "1) Graph\n" <<
         "2) Tests\n" <<
         "3) Presets\n" <<
         "Enter: ";
}

void print_choose_struct() {
    cout << "_____________________________________________________________\n";
    cout << "Select the actions:\n" <<
         "1) Digraph\n" <<
         "2) Non-Digraph\n" <<
         "Enter: ";
}

void print_prog_action_graph() {
    cout << "_____________________________________________________________\n";
    cout << "Select the actions:\n" <<
         "1) Finding the spanning tree of a graph\n" <<
         "2) Finding connected components of a graph\n" <<
         "3) Finding minimum path\n" <<
         "4) Print Graph\n" <<
         "5) Exit\n" <<
         "Enter: ";
}
