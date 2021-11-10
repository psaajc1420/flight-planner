//
// Created by jacob on 11/8/21.
//

#ifndef FLIGHT_PLANNER__DESTINATION_VERTEX_H_
#define FLIGHT_PLANNER__DESTINATION_VERTEX_H_

#include "vertex.h"
#include <list>

template<typename T>
class DestinationVertex : public Vertex<T> {

 public:
  DestinationVertex() = default;
  DestinationVertex(const DestinationVertex<T> &) = default;
  ~DestinationVertex() override = default;
  DestinationVertex &operator=(const DestinationVertex<T> &) = default;
  explicit DestinationVertex(T source) : Vertex<T>(source) {};

  inline T GetSource() override;
  inline const T &GetSource() const override;
  inline void SetSource(T source) override;
};

template<typename T>
void DestinationVertex<T>::SetSource(T source) {
  Vertex<T>::source_ = source;
}

template<typename T>
T DestinationVertex<T>::GetSource() {
  return Vertex<T>::source_;
}

template<typename T>
const T &DestinationVertex<T>::GetSource() const {
  return Vertex<T>::source_;
}
#endif //FLIGHT_PLANNER__DESTINATION_VERTEX_H_
