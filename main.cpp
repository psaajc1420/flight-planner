#include <iostream>
#include "graph_list.h"

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