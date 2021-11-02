//
// Created by jacob on 10/21/21.
//

#ifndef FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_
#define FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_

#include <list>
#include <stack>
#include <vector>
#include "adjacency_list.h"

using std::stack;
using std::vector;
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

  virtual void AddEdge(T &, T &);
  void AddConnection(T &, T &);
  Iterator FindVertex(T &);

  void IterativeBackTracking(T &, T &);

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

  bool StackContainsNode(stack<GraphNode>, const GraphNode&) noexcept;
};

template<typename T>
void GraphList<T>::AddEdge(T &src, T &dest) {
  AddConnection(src, dest);
  AddConnection(dest, src);
}

template<typename T>
typename list<typename AdjacencyList<T>::Node>::iterator GraphList<T>::FindVertex(
    T &data) {
  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    if (it->vertex == data) {
      return it;
    }
  }
  return graph_.end();
}
template<typename T>
void GraphList<T>::AddConnection(T &src, T &dest) {
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
bool GraphList<T>::StackContainsNode(stack<GraphNode> history,
                                     const GraphNode &node) noexcept {
  while (!history.empty()) {
    GraphNode history_node = history.top();
    if (node.vertex == history_node.vertex) {
      return true;
    }
    history.pop();
  }
  return false;
}

template<typename T>
void GraphList<T>::IterativeBackTracking(T &src, T &dest) {
  vector<vector<T>> paths;
  stack<GraphNode> history;
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
}

#endif //FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_
