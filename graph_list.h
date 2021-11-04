//
// Created by jacob on 10/21/21.
//

#ifndef FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_
#define FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_

#include <list>
#include "adjacency_list.h"
#include "vertex.h"

template<typename T>
class GraphList : public AdjacencyList<T> {

  using GraphNode = Vertex<T>;
  using Graph = std::list<GraphNode *>;
  using GraphIterator = typename Graph::iterator;

 public:
  GraphList() = default;
  GraphList(const GraphList<T> &);
  ~GraphList();
  GraphList &operator=(const GraphList<T> &);

  virtual void AddEdge(const T &, const T &);
  void AddConnection(const T &, const T &);
  GraphIterator FindVertex(const T &);

  friend std::ostream &operator<<(std::ostream &os, const GraphList &data) {
    for (auto outer_it = data.graph_.begin(); outer_it != data.graph_.end();
         ++outer_it) {
      os << (*outer_it)->GetSource() << " => ";
      for (auto inner_it = (*outer_it)->GetNeighbors().begin();
           inner_it != (*outer_it)->GetNeighbors().end();
           ++inner_it) {
        os << *inner_it << " ";
      }
      os << std::endl;
    }
    return os;
  }

 private:
  void Copy(const GraphList<T> &);
  void Clear();

  Graph graph_;
};

template<typename T>
GraphList<T>::GraphList(const GraphList<T> &graph) {
  Copy(graph);
}

template<typename T>
GraphList<T>::~GraphList() {
  Clear();
}

template<typename T>
GraphList<T> &GraphList<T>::operator=(const GraphList<T> &graph) {
  if (this != &graph) {
    Clear();
    Copy(graph);
  }

  return *this;
}

template<typename T>
void GraphList<T>::AddEdge(const T &src, const T &dest) {
  AddConnection(src, dest);
  AddConnection(dest, src);
}

template<typename T>
void GraphList<T>::AddConnection(const T &src, const T &dest) {
  auto it = FindVertex(src);
  if (it == graph_.end()) {
    auto *node = new GraphNode;
    node->SetSource(src);
    node->AddNeighbor(dest);
    graph_.push_back(node);
  } else {
    (*it)->AddNeighbor(dest);
  }
}

template<typename T>
typename GraphList<T>::GraphIterator GraphList<T>::FindVertex(const T &data) {
  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    if ((*it)->GetSource() == data) {
      return it;
    }
  }
  return graph_.end();
}

template<typename T>
void GraphList<T>::Copy(const GraphList<T> &graph) {
  for (auto it = graph.graph_.begin(); it != graph.graph_.end(); ++it) {
    graph_.push_back(*it);
  }
}

template<typename T>
void GraphList<T>::Clear() {
  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    delete *it;
  }
}

#endif //FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_
