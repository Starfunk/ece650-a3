#include <algorithm>
#include <iostream>
#include <vector>

#include "headers/node.h"
#include "headers/amatrix.h"

// Base constructor.
AMatrix::AMatrix(void) {}

// Constructor that initializes AMatrix object to input.
AMatrix::AMatrix(unsigned num) {
  number_of_vertices = num;
  // Resize matrix based on the number of vertices.
  matrix.resize(number_of_vertices, std::vector<unsigned>(number_of_vertices));
}

// Create matrix attribute based on input.
void AMatrix::setMatrix(unsigned num) {
  number_of_vertices = num;
  matrix.clear();
  // Resize matrix based on the number of vertices.
  matrix.resize(number_of_vertices, std::vector<unsigned>(number_of_vertices));
}

// Assign edges to the matrix based on input.
void AMatrix::assignEdge(std::vector<unsigned> vec) {
  for (int i = 0; i < vec.size() - 1; i = i + 2) {
    matrix[vec[i]][vec[i + 1]] = 1;
    matrix[vec[i + 1]][vec[i]] = 1;
  }
}

// Output shortest path by printing Parent Id of the last node in
// in visited_nodes (which is guaranteed to be t).
void AMatrix::printShortestPath(void) {
  unsigned n = visited_nodes.size();
  Node parent_id = visited_nodes[n - 1];
  parent_id.printParentId();
}

// Print the Id and Parent Id of each node in visited nodes.
void AMatrix::printVisitedNodes(void) {
  for (Node node : visited_nodes) {
    std::cout << "Node " << node.getId() << ":";
    node.printParentId();
  }
  std::cout << "\n";
}

// Print matrix.
void AMatrix::printMatrix(void) {
  for (int i = 0; i < number_of_vertices; i++) {
    std::cout << "[";
    for (int j = 0; j < number_of_vertices; j++) {
      if (j != number_of_vertices - 1) {
        std::cout << matrix[i][j] << " ";
      } else
        std::cout << matrix[i][j];

      if (j == number_of_vertices - 1) {
        std::cout << "]";
      }
    }
    std::cout << "\n";
  }
}

// Return the number of vertices in the graph.
unsigned AMatrix::getVertexCount(void) { return number_of_vertices; }

std::vector<std::vector<unsigned> > AMatrix::getMatrix(void) { return matrix; }

// Returns true if the node Id is in the graph and false otherwise.
bool AMatrix::inVisitedVertices(unsigned num) {
  if (std::find(visited_vertices.begin(), visited_vertices.end(), num) !=
      visited_vertices.end()) {
    return true;
  } else
    return false;
}

// Returns true if num is greater than the number of vertices.
bool AMatrix::greaterThanVertices(unsigned num) {
	if (num >= number_of_vertices) {
		return true;
	}
	else
		return false;
}

// Returns the (node) Id's Parent Id from visited_nodes.
std::vector<unsigned> AMatrix::findNode(unsigned id) {
  for (Node node : visited_nodes) {
    if (node.getId() == id) {
      return node.getParentId();
    }
  }

  std::cerr << "Error: node not in visited_nodes\n";
  std::vector<unsigned> null;
  return null;
}

// Clears all the helper vectors.
void AMatrix::resetAMatrix(void) {
  visited_nodes.clear();
  visited_vertices.clear();
  to_visit1.clear();
  to_visit2.clear();
}

/*
 * Returns true if there is a shortest path from s to t. Returns
 * false otherwise. If there is a shortest path, then the
 * Parent Id of the last node in Visited Nodes will represent the
 * shortest path.
 */
bool AMatrix::findShortedPath(unsigned s, unsigned t) {
  bool t_found = false;
  if (s > number_of_vertices - 1 or t > number_of_vertices - 1) {
    std::cerr << "Error: s or t is an invalid number\n";
    return false;
  } else if (s == t) {
    std::cout << t << "-" << t << "\n";
    return true;
  }

  std::vector<unsigned> parent_id;
  parent_id.push_back(s);
  Node node_s(s, parent_id);
  visited_nodes.push_back(node_s);
  visited_vertices.push_back(s);

  for (unsigned index = 0; index < number_of_vertices; index++) {
    if (matrix[s][index] == 1) {
      if (index == t) {
        std::vector<unsigned> parent_id = visited_nodes[0].getParentId();
        parent_id.push_back(index);  // the first node is s
        Node node_i(index, parent_id);
        visited_nodes.push_back(node_i);
        return true;
      } else if (inVisitedVertices(index) != true) {
        to_visit1.push_back(index);
        std::vector<unsigned> parent_id = visited_nodes[0].getParentId();
        parent_id.push_back(index);
        Node node_i(index, parent_id);
        visited_nodes.push_back(node_i);
      }
    }
  }

  while (t_found != true) {
    to_visit2 = {};

    if (to_visit1.size() == 0) {
      std::cerr << "Error: no shortest path between " << s << " and "
                << t << "\n";
      return false;
    }

    for (unsigned i = 0; i < to_visit1.size(); i++) {
      unsigned vertex = to_visit1[i];
      for (unsigned index = 0; index < number_of_vertices; index++) {
        if (matrix[vertex][index] == 1) {
          std::vector<unsigned> parent_id = findNode(vertex);
          if (index == t) {
            parent_id.push_back(index);  // the first node is s
            Node node_i(index, parent_id);
            visited_nodes.push_back(node_i);
            return true;
          } else if (!inVisitedVertices(index)) {
            to_visit2.push_back(index);
            parent_id.push_back(index);
            Node node_i(index, parent_id);
            visited_nodes.push_back(node_i);
          }
        }
      }
      if (i == number_of_vertices - 1) {
        std::cerr << "Error: no shortest path between " << s << " and "
                  << t << "\n";
        return false;
      }
    }

    to_visit1 = {};

    if (to_visit2.size() == 0) {
      std::cerr << "Error: no shortest path between " << s << " and "
                << t << "\n";
      return false;
    }

    for (unsigned i = 0; i < to_visit2.size(); i++) {
      unsigned vertex = to_visit2[i];
      for (unsigned index = 0; index < number_of_vertices; index++) {
        if (matrix[vertex][index] == 1) {
          std::vector<unsigned> parent_id = findNode(vertex);
          if (index == t) {
            parent_id.push_back(index);  // the first node is s
            Node node_i(index, parent_id);
            visited_nodes.push_back(node_i);
            return true;
          } else if (!inVisitedVertices(index)) {
            to_visit1.push_back(index);
            parent_id.push_back(index);
            Node node_i(index, parent_id);
            visited_nodes.push_back(node_i);
          }
        }
      }
      if (i == number_of_vertices - 1) {
        std::cerr << "Error: no shortest path between " << s << " and "
                  << t << "\n";
        return false;
      }
    }
  }
  return false;
}
