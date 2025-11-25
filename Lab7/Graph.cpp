// CSCI 311 lab 7
// Graph class skeleton cpp file
// change name to "Graph.cpp"

#include "Graph.h"
#include "Node.h"
#include <iostream>
#include <limits.h>
#include <memory>
#include <queue>

// do not change the headers above
// implement the functions below, but do not add new functions

Graph::Graph() { nodes = {}; }

// Prints an adjacency list representation of the graph.
void Graph::printAdjList() {
  for (int i = 0; i < nodes.size(); i++) {
    std::cout << i << ": ";
    for (std::shared_ptr<Node> neighbor : nodes[i]->neighbors) {
      std::cout << neighbor->id << " ";
    }
    std::cout << std::endl;
  }
}

// Returns true if node v is a neighbor of node u and false otherwise.
bool Graph::isNeighbor(int u, int v) {
  if (nodes[u] == nullptr || nodes[v] == nullptr) {
    std::cout << "Node does not exist" << std::endl;
    return false;
  }
  for (std::shared_ptr<Node> n : nodes[u]->neighbors) {
    if (n->id == v)
      return true;
  }
  return false;
}

void Graph::DFS() {
  if (nodes.empty())
    return;

  int i = 0;
  for (std::shared_ptr<Node> n : nodes) {
    n->id = i;
    n->visited = false;
    n->predecessor = nullptr;
    n->discovered = -1;
    n->finished = -1;
    i++;
  }

  int time = 0;

  for (std::shared_ptr<Node> n : nodes) {
    if (!n->visited) {
      time = DFSVisit(n->id, time);
    }
  }
}

int Graph::DFSVisit(int s, int time) {
  time++;

  nodes[s]->discovered = time;
  nodes[s]->visited = true;

  for (std::shared_ptr<Node> n : nodes[s]->neighbors) {
    if (!(n->visited)) {
      n->predecessor = nodes[s];
      time = DFSVisit(n->id, time);
    }
  }

  time++;
  nodes[s]->finished = time;
  return time;
}

void Graph::BFS(int s) {
  if (s < 0 || s >= nodes.size()) {
    std::cerr << "BFS: input out of bounds" << std::endl;
    return;
  }

  for (std::shared_ptr<Node> n : nodes) {
    n->dist = INT_MAX; // INT_MAX will be a stand-in for infinity
    n->visited = false;
    n->predecessor = nullptr;
  }

  nodes[s]->dist = 0;
  nodes[s]->visited = true;

  std::queue<int> q;
  q.push(s);

  while (q.size() > 0) {
    std::shared_ptr<Node> u = nodes[q.front()];
    q.pop();
    for (std::shared_ptr<Node> v : u->neighbors) {
      if (!(v->visited)) {
        v->dist = u->dist + 1;
        v->visited = true;
        v->predecessor = u;
        q.push(v->id);
      }
    }
  }
}

std::vector<int> Graph::distancesFrom(int s) {
  BFS(s);
  std::vector<int> v;
  for (std::shared_ptr<Node> n : nodes) {
    v.push_back(n->dist);
  }
  return v;
}
