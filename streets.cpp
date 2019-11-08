#include "headers/streets.h"

// Base constructor.
Streets::Streets(void) {}

// Constructor that randomly generates the streets.
Streets::Streets(int s, int n, int l, int c) {
  if (s < 2) {
    std::cerr << "Error: s is less than 2.\n";
    exit(1);
  }
  if (n < 1) {
    std::cerr << "Error: n is less than 1.\n";
    exit(1);
  }
  if (l < 5) {
    std::cerr << "Error: l is less than 5.\n";
    exit(1);
  }
  if (c < 1) {
    std::cerr << "Error: c is less than 1.\n";
    exit(1);
  }
  // Note that since loops go to n - 1, min for num_streets should be 3 not 2.
  this->num_streets = LineSeg::random(2,s); // Define number of streets.
  this->num_segments = n; // This is the upper bound for number of segs per street.
  this->num_wait = LineSeg::random(5,l); // Define number of seconds to wait.

  for (int i = 0; i < this->num_streets; i++) {
    bool used_overlap = false; // True if added a street in the while loop
    Street street(c, this->num_segments);
    if (this->streets.size() > 1) {
      bool street_overlap = this->checkOverlap(street);
      int tries = 0;
      // Make sure the street has no overlaps
      while (street_overlap == true) {
        used_overlap = true;
        // Note that street has not yet been added to this->streets
        Street street(c, this->num_segments);
        street_overlap = this->checkOverlap(street);
        if (street_overlap == false) {
          this->streets.push_back(street);
          break;
        }
        tries += 1;
        if (tries > 25) {
          std::cerr << "Error: Could not generate a valid set"
                    << " of streets in 25 tries.\n";
          exit(3);
        }
      }
    }
    if (used_overlap == false) {

      this->streets.push_back(street);
    }
  }
  // Checking to make sure there is at least one intersection. If not, exit.
  bool street_intersect = false;
  for (int i = 0; i < this->num_streets; i++) {
    Street street = this->streets[i];
    street_intersect = this->checkIntersect(street, i);
    if (street_intersect == true) {
      break;
    }
  }
  // If there are no intersections try 25 times to create a street so that
  // there is one.
  if (street_intersect == false) {
    int intersect_tries = 0;
    while (street_intersect == false) {
      bool street_overlap;
      bool used_overlap = false;

      Street street(c, this->num_segments);
      this->streets.pop_back(); // remove last street in streets
      street_overlap = this->checkOverlap(street);
      // Check that new street does not overlap with any other streets.
      // If it does, regenerate it. Try 25 times.
      int overlap_tries = 0;
      while (street_overlap == true) {
        // Note that street has not yet been added to this->streets
        Street street(c, this->num_segments);
        street_overlap = this->checkOverlap(street);
        if (street_overlap == false) {
          used_overlap = true;
          this->streets.push_back(street);
          break;
        }
        overlap_tries += 1;
        if (overlap_tries > 25) {
          std::cerr << "Error: Could not generate a valid set"
                    << " of streets in 25 tries.\n";
          exit(3);
        }
      }
      if (used_overlap == false) {
        this->streets.push_back(street);
      }
      // Check if there is an intersection
      for (int i = 0; i < this->num_streets; i++) {
        Street street = this->streets[i];
        street_intersect = this->checkIntersect(street, i);
        if (street_intersect == true) {
          // std::cout << "At least one street intersects!\n";
          break;
        }
      }
      // If no intersection with street, increment intersection counter by 1.
      intersect_tries += 1;
      if (intersect_tries > 25) {
        std::cerr << "Error: No streets intersect.\n";
        exit(3);
      }
    }
  }
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

void Streets::printAddStreetsCerr(void) {
  for (int i = 0; i < this->streets.size(); i++) {
    std::cerr << "a \"" << this->street_names[i] << "\" ";
    for (int j = 0; j < this->streets[i].getCoords().size() - 1; j = j + 2) {
      std::cerr << "(" << this->streets[i].getCoords()[j] << ",";
      if (j == this->streets[i].getCoords().size() - 1) {
        std::cerr << this->streets[i].getCoords()[j+1] << ")";
      }
      else {
        std::cerr << this->streets[i].getCoords()[j+1] << ") ";
      }
    }
    std::cerr << "\n";
  }
}

void Streets::printStreetsDebug (void) {
  for (int i = 0; i < this->streets.size(); i++) {
    Street street = this->streets[i];
    street.printCoords();
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

int Streets::getNumWait(void) {
  return this->num_wait;
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

// Returns true if the input street does intersect with one of the streets
// in the vector "streets".
// Note that street1 has been added to this->streets.
// Index is the index of street1 in streets
bool Streets::checkIntersect(Street street1, int index) {
  bool intersects = false;
  for (LineSeg lineseg1: street1.getLineSegs()) {
    for (int i = 0; i < this->num_streets; i++) {
      if (i == index) {
        continue;
      }
      Street street2 = this->streets[i];
      for (LineSeg lineseg2: street2.getLineSegs()) {
        if (lineseg2.intersect(lineseg1) == true) {
          intersects = true;
          break;
        }
      }
      if (intersects == true) {
        break;
      }
    }
    if (intersects == true) {
      break;
    }
  }
  return intersects;
}
