//
// Created by jacob on 10/20/21.
//

#ifndef FLIGHT_PLANNER__ADJACENCY_LIST_H_
#define FLIGHT_PLANNER__ADJACENCY_LIST_H_

#include <iostream>
#include <list>

using std::list;

template<typename T>
class AdjacencyList {

 protected:
  struct Node {
    T vertex;
    list<T> neighbors;
  };

 public:
  AdjacencyList() = default;
  virtual void AddEdge(T&, T&) = 0;

};


#endif //FLIGHT_PLANNER__ADJACENCY_LIST_H_
