#include <iostream>
#include <stack>
#include <vector>

#include "graph_list.h"
#include "vertex.h"

using namespace std;

template <typename T>
vector<vector<T>> IterativeBackTracking(const T &src, const T &dest) {
  vector<vector<T>> paths;
  stack<Vertex<T>> history;
  auto vertex_it = FindVertex(src);

  history.push(*vertex_it);
  while (!history.empty()) {
    if (history.top() == dest) {

    } else {
      for (auto it = history.top().neighbors.begin();
           it != history.top().neighbors.end(); ++it) {


      }
    }
  }

  return paths;
}

int main() {
  GraphList<int> graph_list;
  vector<int> sources = {0, 0, 1, 1, 1, 2, 2, 5, 5};
  vector<int> destinations = {4, 3, 2, 4, 5, 3, 5, 3, 4};

  for (int i = 0; i < sources.size(); i++) {
    graph_list.AddEdge(sources.at(i), destinations.at(i));
  }

  std::cout << graph_list << std::endl;
}