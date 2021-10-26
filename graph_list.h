//
// Created by jacob on 10/21/21.
//

#ifndef FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_
#define FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_

#include <list>
#include <stack>
#include "adjacency_list.h"

using std::stack;
using std::list;
using std::ostream;
using std::cout;
using std::endl;

template<typename T>
class GraphList : public AdjacencyList<T> {

  using GraphNode = typename AdjacencyList<T>::Node;
  using Graph = list<GraphNode>;
  using Iterator = typename Graph::iterator;

 public:
  GraphList() = default;
  GraphList(const GraphList<T> &) = default;
  ~GraphList() = default;
  GraphList &operator=(const GraphList<T> &) = default;

  virtual void AddEdge(T, T);
  void AddConnection(T, T);
  Iterator FindVertex(T);
  void IterativeBackTracking();

  bool Empty() const noexcept;

  friend ostream &operator<<(ostream &os, const GraphList &data) {
    for (auto outer_it = data.graph_.begin(); outer_it != data.graph_.end();
         ++outer_it) {
      os << outer_it->vertex << " => ";
      for (auto inner_it = (*outer_it).neighbors.begin();
           inner_it != (*outer_it).neighbors.end();
           ++inner_it) {
        os << *inner_it << " ";
      }
      os << endl;
    }
    return os;
  }

 private:
  Graph graph_;
};

template<typename T>
void GraphList<T>::AddEdge(T src, T dest) {
  AddConnection(src, dest);
  AddConnection(dest, src);
}

template<typename T>
typename list<typename AdjacencyList<T>::Node>::iterator GraphList<T>::FindVertex(
    T data) {
  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    if (it->vertex == data) {
      return it;
    }
  }
  return graph_.end();
}
template<typename T>
void GraphList<T>::AddConnection(T src, T dest) {
  auto it = FindVertex(src);
  if (it == graph_.end()) {
    list<T> new_list;
    new_list.push_back(dest);
    GraphNode node;
    node.vertex = src;
    node.neighbors = new_list;
    graph_.push_back(node);
  } else {
    it->neighbors.push_back(dest);
  }
}

template<typename T>
bool GraphList<T>::Empty() const noexcept {
  return graph_.empty();
}

template<typename T>
void GraphList<T>::IterativeBackTracking() {
  stack<Graph> history;
  list<GraphNode> path;
  Graph graph;
  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    history.push(*it);
  }

  while (!history.empty()) {
    if (history.top().empty()) {
      if (!path.empty()) path.pop();
      history.pop();
    } else {
      GraphNode node = history.top().front();
      history.top().pop_front();

    }
  }
}

#endif //FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_
