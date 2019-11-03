#include <iostream>
#include <vector>
#include <fstream>
#include "headers/lineseg.h"
#include "headers/street.h"




// Constructor
Street::Street(void) {}

// Constructor that randomly generates the street
Street::Street(int range, int segments) {
  int lower = -range;
  int upper = range;
  unsigned int segment_count = 0;
  unsigned int tries = 0;
  // NEED TO CHECK THAT Segments > 5, do the handling in rgen
  // segments determines the number of line segments in the street
  if (segments >= 5) {
    segments = LineSeg::random(5,segments);
  }

  int x_a = LineSeg::random(lower,upper);
  int y_a = LineSeg::random(lower,upper);
  int x_b = LineSeg::random(lower,upper);
  int y_b = LineSeg::random(lower,upper);
  while (x_a == x_b && y_a == y_b) {
    x_a = LineSeg::random(lower,upper);
    y_a = LineSeg::random(lower,upper);
    x_b = LineSeg::random(lower,upper);
    y_b = LineSeg::random(lower,upper);
    tries++;
    if (tries > 25) {
      std::cerr << "Error: Could not generate a nonzero line segment in 25 tries.\n";
      exit(1);
    }
  }
  this->coords.push_back(x_a);
  this->coords.push_back(y_a);
  this->coords.push_back(x_b);
  this->coords.push_back(y_b);
  segment_count += 1;

  while (segment_count < segments) {
    //  Create next set of coordinates
    x_a = LineSeg::random(lower,upper);
    y_a = LineSeg::random(lower,upper);
    while (x_a == x_b && y_a == y_b) {
      x_a = LineSeg::random(lower,upper);
      y_a = LineSeg::random(lower,upper);
      tries++;
      if (tries > 25) {
        std::cerr << "Error: Could not generate a nonzero line segment in 25 tries.\n";
        exit(1);
      }
    }
    this->coords.push_back(x_a);
    this->coords.push_back(y_a);
    segment_count += 1;
    if (segment_count == segments) {
      break;
    }

    //  Create next set of coordinates
    x_b = LineSeg::random(lower,upper);
    y_b = LineSeg::random(lower,upper);
    while (x_a == x_b && y_a == y_b) {
      x_b = LineSeg::random(lower,upper);
      y_b = LineSeg::random(lower,upper);
      tries++;
      if (tries > 25) {
        std::cerr << "Error: Could not generate a nonzero line segment in 25 tries.\n";
        exit(1);
      }
    }
    this->coords.push_back(x_b);
    this->coords.push_back(y_b);
    segment_count += 1;
    if (segment_count == segments) {
      break;
    }
  }
  // Generate street in terms of line segments, linesegs, from coords.
  LineSeg lineseg(this->coords[0],this->coords[1],
                  this->coords[2],this->coords[3]);
  this->linesegs.push_back(lineseg);

  for (int j = 2; j < coords.size() - 2; j = j + 2) {
    LineSeg lineseg(coords[j],coords[j+1],coords[j+2],coords[j+3]);

    // std::cout << "checkValid: " << this->checkValid(lineseg) << "\n";
    while (this->checkValid(lineseg) == false) {
      // std::cout << this->checkValid(lineseg);
      this->coords[j+2] = LineSeg::random(lower,upper);
      this->coords[j+3] = LineSeg::random(lower,upper);
      LineSeg lineseg(this->coords[j],this->coords[j+1],
                      this->coords[j+2],this->coords[j+3]);
      tries += 1;
      if (tries > 25) {
        std::cerr << "Error: Could not generate a valid line segment in 25 tries.\n";
        exit(1);
      }
    }
    this->linesegs.push_back(lineseg);
  }

  // for (LineSeg lineseg: this->linesegs) {
  //   lineseg.printLineSeg();
  // }
}

void Street::printCoords(void) {
  std::cout << "Printing coords: \n";
  std::cout << "[";
  for (int i = 0; i < this->coords.size(); i++) {
    if (i == this->coords.size() - 1) {
      std::cout << coords[i] << "]\n";
    }
    else {
      std::cout << coords[i] << ", ";
    }
  }
}

std::vector<LineSeg> Street::getLineSegs(void) {
  return this->linesegs;
}

std::vector<int> Street::getCoords(void) {
  return this->coords;
}

// Check if a new line seg will overlap or intersect with the rest of the
// line segs on the street. Return true if valid, false otherwise.
bool Street::checkValid(LineSeg& lineseg) {
  bool valid = true;

  // End the loop before testing the final line segment in linesegs, since by
  // definition it will intersect will the input lineseg.
  for (int i = 0; i < this->linesegs.size(); i++) {
    if (lineseg.overlap(this->linesegs[i]) == true) {
      // std::cout << "PRINTING INTERSECT: " << lineseg.intersect(this->linesegs[i]) << "\n";
      // std::cout << "PRINTING OVERLAP: " << lineseg.overlap(this->linesegs[i]) << "\n";
      valid = false;
      break;
    }
  }

  return valid;
}
