#include "headers/street.h"

// Base constructor
Street::Street(void) {}

// Constructor that randomly generates the street
Street::Street(int range, int segments) {
  int lower = -range;
  int upper = range;
  unsigned int segment_count = 0;
  unsigned int tries = 0;
  int line_segments = LineSeg::random(1,segments); // n option

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

  while (segment_count < line_segments) {
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
    if (segment_count == line_segments) {
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
    if (segment_count == line_segments) {
      break;
    }
  }
  // Generate street in terms of line segments, linesegs, from coords.
  LineSeg lineseg(this->coords[0],this->coords[1],
                  this->coords[2],this->coords[3]);
  this->linesegs.push_back(lineseg);

  for (int j = 2; j < coords.size() - 2; j = j + 2) {
    tries = 0;
    LineSeg lineseg(coords[j],coords[j+1],coords[j+2],coords[j+3]);

    bool is_valid = this->checkValid(lineseg);
    // If the street is not valid, regenerate until it is valid.
    while (is_valid == false) {
      this->coords[j+2] = LineSeg::random(lower,upper);
      this->coords[j+3] = LineSeg::random(lower,upper);

      LineSeg lineseg(this->coords[j],this->coords[j+1],
                      this->coords[j+2],this->coords[j+3]);
      is_valid = this->checkValid(lineseg);
      tries += 1;
      if (tries > 25) {
        std::cerr << "Error: Could not generate a valid line segment in 25 tries.\n";
        exit(1);
      }
    }
    this->linesegs.push_back(lineseg);
  }

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
      valid = false;
      break;
    }
    if (i != this->linesegs.size() - 1 &&
        lineseg.intersect(this->linesegs[i]) == true) {
      valid = false;
      break;
    }
  }
  return valid;
}
