//
// Created by jacob on 10/21/21.
//

#ifndef FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_
#define FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_

#include <list>
#include "adjacency_list.h"
#include "vertex.h"
#include "source_vertex.h"
#include "destination_vertex.h"

template<typename T>
class GraphList : public AdjacencyList<T> {

  using SourceNode = SourceVertex<T>;
  using DestinationNode = DestinationVertex<T>;
  using GraphNode = Vertex<T>;
  using Graph = std::list<SourceNode *>;

 public:
  using GraphIterator = typename Graph::iterator;

  GraphList() = default;
  GraphList(const GraphList<T> &);
  ~GraphList();
  GraphList &operator=(const GraphList<T> &);

  virtual void AddEdge(const T &, const T &);
  void AddConnection(const T &, const T &);
  GraphIterator FindVertex(const T &);
  inline void InitIterators();
  GraphIterator Begin();
  GraphIterator End();

  friend std::ostream &operator<<(std::ostream &os, const GraphList &data) {
    for (auto outer_it = data.graph_.begin(); outer_it != data.graph_.end();
         ++outer_it) {
      os << (*outer_it)->GetSource() << " => ";
      SourceNode * vertex = *outer_it;
      for (auto inner_it = vertex->GetNeighbors().begin();
           inner_it != vertex->GetNeighbors().end();
           ++inner_it) {
        os << **inner_it << " ";
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

  auto destination_node = new DestinationNode;
  destination_node->SetSource(dest);
  if (it == graph_.end()) {
    auto source_node = new SourceNode;
    source_node->SetSource(src);
    source_node->AddNeighbor(destination_node);
    graph_.push_back(source_node);
  } else {
    (*it)->AddNeighbor(destination_node);
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

  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    auto source_node = new SourceNode;
    source_node->SetSource((*it)->GetSource());
    for (auto neighbor_it = (*it)->GetNeighbors().begin();
         neighbor_it != (*it)->GetNeighbors().end(); ++neighbor_it) {
      auto destination_node = new DestinationNode;
      destination_node->SetSource((*neighbor_it)->GetSource());
      source_node->AddNeighbor(destination_node);
    }
  }
}

template<typename T>
void GraphList<T>::Clear() {
  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    SourceNode* source_node = *it;
    for (auto neighbor_it = source_node->GetNeighbors().begin();
         neighbor_it != source_node->GetNeighbors().end(); ++neighbor_it) {
      delete *neighbor_it;
    }
    delete source_node;
  }
}

template<typename T>
void GraphList<T>::InitIterators() {
  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    (*it)->InitIterator();
  }
}

template<typename T>
typename GraphList<T>::GraphIterator GraphList<T>::Begin() {
  return graph_.begin();
}

template<typename T>
typename GraphList<T>::GraphIterator GraphList<T>::End() {
  return graph_.end();
}

#endif //FLIGHT_PLANNER_CMAKE_BUILD_DEBUG_GRAPH_LIST_H_
