#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <vector>
#include <typeinfo>

#include "graph_list.h"
#include "vertex.h"

using namespace std;

struct City {
  string name_;
  int price_;
  int cost_;
  string airline_;
  City() = default;
  explicit City(string name) : name_{name} {}
  City(string name, int cost, int price, string airline)
      : name_{name}, price_{price}, cost_{cost}, airline_{airline} {}

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
bool contains(stack<Vertex<T> *> &path, Vertex<T>* source) {
  stack<Vertex<T> *> temp;

  bool found = false;
  while (!path.empty()) {
    if (*path.top() == *source) found = true;
    temp.push(path.top());
    path.pop();
  }

  while (!temp.empty()) {
    path.push(temp.top());
    temp.pop();
  }

  return found;
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
    if (path.top() == *destinationItr) {
      paths.push_back(path);
      path.pop();
    } else {
      auto it = graph.FindVertex(path.top()->GetSource());

      auto temp = (*it)->GetIterator();

      if (temp == (*it)->GetNeighbors().end()) {
        (*it)->InitIterator();
        path.pop();
      } else if (contains(path, *it)) {
        (*it)->IncrementIterator();
      } else {
        (*it)->IncrementIterator();
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

    int price = rand() % 300;
    int cost = rand() % 300;
    string airline = airlines[i];
    City source_city(sources.at(i), price, cost, airline);
    City destination_city(destinations.at(i), price, cost, airline);
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