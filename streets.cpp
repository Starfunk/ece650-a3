#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "headers/lineseg.h"
#include "headers/street.h"
#include "headers/streets.h"


// Constructor
Streets::Streets(void) {}

// Constructor that randomly generates the streets.
Streets::Streets(int s, int n, int c) {
  // if (!s) {
  //   s = 10;
  // }
  unsigned int tries = 0;
  // Check that input is valid.
  if (s < 2) {
    std::cerr << "Error: s is less than 2.\n";
    exit(1);
  }
  if (n < 5) {
    std::cerr << "Error: n is less than 5.\n";
    exit(1);
  }
  if (c < 1) {
    std::cerr << "Error: c is less than 1.\n";
    exit(1);
  }

  this->num_streets = LineSeg::random(2,s);
  // std::cout << "number of streets: " << this->num_streets << "\n";
  this->num_segments = LineSeg::random(5,n);
  // this->num_range = LineSeg::random(-c,c);

  for (int i = 0; i < this->num_streets; i++) {
    Street street(c, this->num_segments);
    if (this->streets.size() > 1) {
      while (this->checkOverlap(street) == true) {
        Street street(c, this->num_segments);
        tries += 1;
        if (tries > 25) {
          std::cerr << "Error: Could not generate a valid set"
                    << " of streets in 25 tries.\n";
          exit(1);
        }
      }
    }
    this->streets.push_back(street);
    // this->street_names.push_back(i);
  }

  // for (int i = 0; i < this->num_streets; i++) {
  //   this->streets[i].printCoords();
  // }
}

void Streets::printAddStreets(void) {
  for (int i = 0; i < this->streets.size(); i++) {
    std::cout << "a \"" << this->street_names[i] << "\" ";
    for (int j = 0; j < this->streets[i].getCoords().size() - 1; j = j + 2) {
      std::cout << "(" << this->streets[i].getCoords()[j] << ",";
      if (j == this->streets[i].getCoords().size() - 1) {
        std::cout << this->streets[i].getCoords()[j+1] << ")";
      }
      else {
        std::cout << this->streets[i].getCoords()[j+1] << ") ";
      }
    }
    std::cout << "\n";
  }
}

void Streets::generateStreetNames(void) {
  int counter = 0;
  int j;
  std::string street_name;

  for (int i = 0; i < this->num_streets; i++) {
    j = i;
    if (i > this->alphabet.size()) {
      j = i % this->alphabet.size();
    }
    for (int j = 0; j < counter; j++) {
      street_name.append("a");
    }
    street_name.append(this->alphabet[j]);
    this->street_names.push_back(street_name);

    if (i != 0) {
      if (this->alphabet.size() % i == 0) {
        counter += 1;
      }
    }
  }
}

void Streets::printRemoveStreets(void) {
  for (std::string street_name : this->street_names) {
    std::cout << "r \"" << street_name << "\"\n";
  }
}

void Streets::printGraph(void) {
  std::cout << "g\n";
}

// Returns true if the input street does overlap with one of the streets
// in the vector "streets".
bool Streets::checkOverlap(Street street1) {
  bool overlaps = false;
  for (LineSeg lineseg1: street1.getLineSegs()) {
    for (Street street2: this->streets) {
      for (LineSeg lineseg2: street2.getLineSegs()) {
        if (lineseg2.overlap(lineseg1) == true) {
          overlaps = true;
          break;
        }
      }
      if (overlaps == true) {
        break;
      }
    }
    if (overlaps == true) {
      break;
    }
  }
  return overlaps;
}
