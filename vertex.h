//
// Created by jacob on 11/3/21.
//

#ifndef FLIGHT_PLANNER__VERTEX_H_
#define FLIGHT_PLANNER__VERTEX_H_

template<typename T>
class Vertex {

 public:
  Vertex() = default;
  Vertex(const Vertex<T> &) = default;
  virtual ~Vertex() = default;
  Vertex &operator=(const Vertex<T> &) = default;
  explicit Vertex(T source) : source_{source} {};

  virtual T GetSource() = 0;
  virtual const T &GetSource() const = 0;
  virtual void SetSource(T source) = 0;

  friend bool operator==(const Vertex<T>& lhs, const Vertex& rhs) {
    return lhs.source_ == rhs.source_;
  }

  friend std::ostream &operator<<(std::ostream &os, const Vertex &vertex) {
    os << vertex.source_;
    return os;
  }

 protected:
  T source_;
};

#endif //FLIGHT_PLANNER__VERTEX_H_
