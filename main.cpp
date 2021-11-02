#include <iostream>
#include "graph_list.h"

int main() {
  GraphList<int> graph_list;
  vector<int> sources = {0, 0, 1, 1, 1, 2, 2, 5, 5};
  vector<int> destinations = {4, 3, 2, 4, 5, 3, 5, 3, 4};

  for (int i = 0; i < sources.size(); i++) {
    graph_list.AddEdge(sources.at(i), destinations.at(i));
  }

  std::cout << graph_list << std::endl;
}