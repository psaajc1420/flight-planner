#include <iostream>
#include <stack>
#include "graph_list.h"

using std::stack;


template <typename T>
void IterativeBackTracking(const list<list<T>> &graph) {
  stack<T> history;
  for (auto outer_it = graph.begin(); outer_it != graph.end(); ++outer_it) {
    for (auto inner_it = (*outer_it).begin(); inner_it != (*outer_it).end();
         ++inner_it) {
    }
  }
}

int main() {
  GraphList<int> graph_list;
  graph_list.AddEdge(0, 4);
  graph_list.AddEdge(0, 3);
  graph_list.AddEdge(1, 2);
  graph_list.AddEdge(1, 4);
  graph_list.AddEdge(1, 5);
  graph_list.AddEdge(2, 3);
  graph_list.AddEdge(2, 5);
  graph_list.AddEdge(5, 3);
  graph_list.AddEdge(5, 4);

  std::cout << graph_list << std::endl;
}