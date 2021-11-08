//
// Created by jacob on 11/8/21.
//

#ifndef FLIGHT_PLANNER__SOURCE_VERTEX_H_
#define FLIGHT_PLANNER__SOURCE_VERTEX_H_

#include "vertex.h"

#include <list>

template<typename T>
class SourceVertex : public Vertex<T> {
 public:
  SourceVertex() = default;
  SourceVertex(const SourceVertex<T> &) = default;
  ~SourceVertex() override = default;
  SourceVertex &operator=(const SourceVertex<T> &) = default;

  inline void AddNeighbor(Vertex<T> *);
  inline const std::list<Vertex<T> *> &GetNeighbors() const;
  inline void InitIterator();
  inline void IncrementIterator();
  inline typename std::list<Vertex<T> *>::iterator GetIterator();

  inline T GetSource() override;
  inline const T &GetSource() const override;
  inline void SetSource(T source) override;

 private:
  std::list<Vertex<T> *> neighbors_;
  typename std::list<Vertex<T> *>::iterator neighbors_itr_;
};

template<typename T>
const std::list<Vertex<T> *> &SourceVertex<T>::GetNeighbors() const {
  return neighbors_;
}

template<typename T>
void SourceVertex<T>::AddNeighbor(Vertex<T> *neighbor) {
  neighbors_.push_back(neighbor);
}

template<typename T>
void SourceVertex<T>::InitIterator() {
  neighbors_itr_ = neighbors_.begin();
}

template<typename T>
void SourceVertex<T>::IncrementIterator() {
  ++neighbors_itr_;
}

template<typename T>
typename std::list<Vertex<T> *>::iterator SourceVertex<T>::GetIterator() {
  return neighbors_itr_;
}

template<typename T>
T SourceVertex<T>::GetSource() {
  return Vertex<T>::source_;
}

template<typename T>
const T &SourceVertex<T>::GetSource() const {
  return Vertex<T>::source_;
}

template<typename T>
void SourceVertex<T>::SetSource(T source) {
  Vertex<T>::source_ = source;
}

#endif //FLIGHT_PLANNER__SOURCE_VERTEX_H_
