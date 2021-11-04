//
// Created by jacob on 11/3/21.
//

#ifndef FLIGHT_PLANNER__VERTEX_H_
#define FLIGHT_PLANNER__VERTEX_H_

#include <list>

template<typename T>
class Vertex {

 public:
  Vertex() = default;
  Vertex(const Vertex<T>&) = default;
  ~Vertex() = default;
  Vertex& operator=(const Vertex<T>&) = default;
  explicit Vertex(const T &source) : source_{source} {};

  inline T GetSource();
  inline const T &GetSource() const;
  inline void AddNeighbor(const T &);
  inline void SetSource(T source);
  inline const std::list<T>& GetNeighbors() const;

 private:

  T source_;
  std::list<T> neighbors_;

};

template<typename T>
void Vertex<T>::SetSource(T source) {
  source_ = source;
}

template<typename T>
inline T Vertex<T>::GetSource() {
  return source_;
}

template<typename T>
const T &Vertex<T>::GetSource() const {
  return source_;
}

template<typename T>
const std::list<T>& Vertex<T>::GetNeighbors() const {
  return neighbors_;
}

template<typename T>
void Vertex<T>::AddNeighbor(const T &neighbor) {
  neighbors_.push_back(neighbor);
}

#endif //FLIGHT_PLANNER__VERTEX_H_
