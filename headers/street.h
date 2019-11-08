#ifndef STREET_H
#define STREET_H
#include <iostream>
#include <vector>
#include <fstream>
#include "lineseg.h"

class Street {
 public:
  Street();
  Street(int range, int segments);
  void printCoords(void);
  std::vector<LineSeg> getLineSegs(void);
  std::vector<int> getCoords(void);
  bool checkValid(LineSeg& lineseg);

 private:
  std::vector<LineSeg> linesegs; // A vector of all the linesegs in the street.
  std::vector<int> coords;
};

#endif
