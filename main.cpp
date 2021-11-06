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
  explicit City(string name, int cost, int price, string airline)
      : name_{name}, price_{price}, cost_{cost}, airline_{airline} {}

  bool operator==(const City &rhs) const {
    return this->name_ == rhs.name_;
  }
};

void printItinerary(stack<Vertex<City *> *> &stack) {
  if (stack.empty()) return;

  string city = stack.top()->GetSource()->name_;

  stack.pop();
  printItinerary(stack);
  cout << city << " ";
}

template<typename T>
bool contains(stack<Vertex<T> *> &path, const T &source) {
  stack<Vertex<T> *> temp;

  bool found = false;
  while (!path.empty()) {
    if (*path.top()->GetSource() == *source) found = true;
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
      auto it = path.top()->GetIterator();

      if (it == path.top()->GetNeighbors().end()) {
        path.top()->InitIterator();
        path.pop();
      } else if (contains(path, *it)) {
        path.top()->IncrementIterator();
      } else {
        path.top()->IncrementIterator();
        path.push(*graph.FindVertex(*it));
      }
    }
  }

  return paths;
}

int main() {

  srand(time(nullptr));
  GraphList<City *> graph_list;
  vector<string> sources = {"Dallas", "Austin", "Dallas", "Austin"};
  vector<string> destinations = {"Austin", "Houston", "Houston", "Chicago"};

  vector<City *> cities;

  for (int i = 0; i < sources.size(); i++) {

    int price = rand() % 300;
    int cost = rand() % 300;
    string airline = "Southwest";
    City *source_city = new City(sources.at(i), price, cost, airline);
    City *destination_city =
        new City(destinations.at(i), price, cost, airline);
    graph_list.AddEdge(source_city, destination_city);
    cities.push_back(source_city);
    cities.push_back(destination_city);
  }
//  std::cout << graph_list << std::endl;

  for (auto it = graph_list.Begin(); it != graph_list.End(); ++it) {
    cout << (*it)->GetSource()->name_ << endl;
  }

  City *source = new City("Dallas");
  City *destination = new City("Houston");

  vector<stack<Vertex<City *> *>>
      itineraries = IterativeBackTracking(graph_list, source, destination);

  for (auto it = itineraries.begin(); it != itineraries.end(); ++it) {
    printItinerary(*it);
    cout << endl;
  }

  delete source;
  delete destination;

  for (auto it = cities.begin(); it != cities.end(); ++it) {
    delete *it;
  }

  return 0;
}