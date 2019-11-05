#include <iostream>
#include <vector>

#include "headers/node.h"

// Constructor
Node::Node(void) {}

// Constructor that initializes id and parent_id
Node::Node(unsigned num, std::vector<unsigned> vec) {
  id = num;
  parent_id = vec;
}

// Returns node's Id.
unsigned Node::getId(void) { return id; }

// Returns node's Parent Id.
std::vector<unsigned> Node::getParentId(void) { return parent_id; }

// Print node's Parent Id.
void Node::printParentId(void) {
  for (unsigned i = 0; i < parent_id.size(); i++) {
    if (i == parent_id.size() - 1) {
      std::cout << parent_id[i];
    } else
      std::cout << parent_id[i] << "-";
  }
  std::cout << "\n";
}
