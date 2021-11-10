#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <vector>
#include "graph_list.h"
#include "vertex.h"

using namespace std;

struct City {
  string name_;
  string airline_;
  City() = default;
  explicit City(string name) : name_{name} {}
  City(string name, string airline)
      : name_{name}, airline_{airline} {}

  bool operator==(const City &rhs) const {
    return name_ == rhs.name_;
  }

  friend std::ostream &operator<<(std::ostream &os, const City &city) {
    os << city.name_ << "(" << city.airline_ << ") ";
    return os;
  }
};

void PrintItinerary(stack<Vertex<City> *> &stack) {
  if (stack.empty()) return;

  City city = stack.top()->GetSource();

  stack.pop();
  PrintItinerary(stack);
  cout << city.name_ << "(" << city.airline_ << ") ";
}

template<typename T>
bool contains(stack<Vertex<T> *> path, Vertex<T> *source) {

  while (!path.empty()) {
    if (*path.top() == *source) return true;
    path.pop();
  }

  return false;
}

template<typename T>
vector<stack<Vertex<T> *>> IterativeBackTracking(GraphList<T> &graph,
                                                 const T &src,
                                                 const T &dest) {
  vector<stack<Vertex<T> *>> paths;
  stack<Vertex<T> *> path;

  auto sourceItr = graph.FindVertex(src);
  auto destinationItr = graph.FindVertex(dest);

  path.push(*sourceItr);
  graph.InitIterators();
  while (!path.empty()) {
    if (*path.top() == **destinationItr) {
      paths.push_back(path);
      path.pop();
    } else {
      auto source_it = graph.FindVertex(path.top()->GetSource());

      auto it = (*source_it)->GetIterator();

      if (it == (*source_it)->GetNeighbors().end()) {
        (*source_it)->InitIterator();
        path.pop();
      } else if (contains(path, *it)) {
        (*source_it)->IncrementIterator();
      } else {
        (*source_it)->IncrementIterator();
        path.push(*it);
      }
    }
  }

  return paths;
}

int main() {

  srand(time(nullptr));
  GraphList<City> graph_list;
  vector<string> sources = {"Dallas", "Dallas", "Austin", "Dallas", "Austin"};
  vector<string>
      destinations = {"Austin", "Austin", "Houston", "Houston", "Chicago"};
  vector<string>
      airlines = {"Spirit", "American", "United", "Spirit", "American"};

  for (int i = 0; i < sources.size(); i++) {
    string airline = airlines[i];
    City source_city(sources.at(i), airline);
    City destination_city(destinations.at(i), airline);
    graph_list.AddEdge(source_city, destination_city);

  }

  cout << graph_list << endl;

  City source("Dallas");
  City destination("Houston");

  vector<stack<Vertex<City> *>>
      itineraries = IterativeBackTracking(graph_list, source, destination);

  for (auto it = itineraries.begin(); it != itineraries.end(); ++it) {
    PrintItinerary(*it);
    cout << endl;
  }

  return 0;
}