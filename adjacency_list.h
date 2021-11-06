//
// Created by jacob on 10/20/21.
//

#ifndef FLIGHT_PLANNER__ADJACENCY_LIST_H_
#define FLIGHT_PLANNER__ADJACENCY_LIST_H_

#include <iostream>
#include <list>

template<typename T>
class AdjacencyList {
 public:
  AdjacencyList() = default;
  virtual void AddEdge(const T &, const T &) = 0;
};

#endif //FLIGHT_PLANNER__ADJACENCY_LIST_H_
