#ifndef STREETS_H
#define STREETS_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "lineseg.h"
#include "street.h"

class Streets {
 public:
  Streets();
  Streets(int num_streets, int num_segments, int num_wait, int num_range);
  bool checkOverlap(Street street);
  bool checkIntersect(Street street, int index);
  void printAddStreets(void);
  void printStreetsDebug(void); // When num streets in this->streets < this->num_streets
  void printAddStreetsCerr(void); // Prints to cerr
  void printRemoveStreets(void);
  void printGraph(void);
  void generateStreetNames(void);
  int getNumWait(void);

 private:
  std::vector<Street> streets;
  std::vector<std::string> street_names;
  std::vector<std::string> alphabet = {"a","b","c","d","e","f","g","h","i","j",
                                       "k","l","m","n","o","p","q","r","s","t",
                                       "u","v","w","x","y","z"};
  int num_streets;
  int num_segments; // upper bound on segments
  int num_wait;
};

#endif
