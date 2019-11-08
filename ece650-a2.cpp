#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <signal.h>
#include "headers/node.h"
#include "headers/amatrix.h"

AMatrix matrix;

int main() {
  while (!std::cin.eof()) {
    // Read a line of input until EOL and store in a string.
    std::string line;

    // Get the input line. The last character is the newline '\n'.
    std::getline(std::cin, line);

    // Don't print the s command, since it is already printed when the user
    // enters it in the driver process.
    if (line[0] != 's') {
      std::cout << line << std::endl;
    }
    // Create an input stream based on the line.
    // We will use the input stream to parse the line.
    std::istringstream input(line);
    // if (line == "A1 FINISHED\n") {
    //   std::cout << "A2 Finished\n";
    //   std::cout.flush();
    // }
	  if (std::cin.eof()) {
      // kill (0, SIGTERM);
      // exit(0);
	    break;
	  }
    /* We expect each line to contain a list of numbers.
    This vector will store the numbers.
    They are assumed to be unsigned (i.e., positive) */
    std::vector<unsigned> nums;

    // Store the input command.
    char command;
    input >> command;

    // Create adjacency matrix if input is V.
    if (command == 'V') {
      unsigned number_of_vertices;
      while (!input.eof()) {
		input >> number_of_vertices;
		if (input.fail()) {
			std::cerr << "Error: parsing V command\n";
			break;
		}
	  }
      matrix.setMatrix(number_of_vertices);
    }

    // Assign edges to matrix if E is input.
    else if (command == 'E') {
      unsigned num;
      char separator;
      bool error = false;
      input >> separator;
      input >> separator;
      while (!input.eof()) {
        if (input.fail()) {
		  error = true;
          std::cerr << "Error: parsing E command\n";
          break;
        }
        input >> num;
        if (matrix.greaterThanVertices(num)) {
			error = true;
			std::cerr << "Error: edge exceeds vertex count\n";
			break;
		}
        nums.push_back(num);
        input >> separator;
        if (input.fail()) {
		  error = true;
          std::cerr << "Error: parsing E command\n";
          break;
        }
        input >> num;
        if (matrix.greaterThanVertices(num)) {
			error = true;
			std::cerr << "Error: edge exceeds vertex count\n";
			break;
		}
        nums.push_back(num);
        input >> separator;
        input >> separator;
        input >> separator;
      }
      if (error == false) {
        matrix.assignEdge(nums);
	    }
    }

    // Output shortest path between vertices s and t.
    else if (command == 's') {
      bool failedparse = false;
      unsigned s;
      unsigned t;
    while (!input.eof()) {
		  input >> s;
		  if (input.fail()) {
			  std::cerr << "Error: parsing s command\n";
        failedparse = true;
			  break;
		  }
		  input >> t;
		  if (input.fail()) {
			  std::cerr << "Error: parsing s command\n";
        failedparse = true;
			  break;
		  }
	  }

    if (failedparse == false) {
  	  if (matrix.findShortedPath(s, t)) {
  		  if (s != t) {
  		    matrix.printShortestPath();
          std::cout.flush();
  		  }
  	  }
  	  matrix.resetAMatrix();
      }
    }
  }
  return 0;
}
