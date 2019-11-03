#ifndef LINESEG_H
#define LINESEG_H

#include <iostream>
#include <vector>

class LineSeg {
 public:
  LineSeg();
  // Random number constructor.
  LineSeg(int lower, int upper);
  // Manual assignment constructor.
  LineSeg(int a, int b, int c, int d);
  float getSlope(void);
  float getB(void);
  bool getFlag(void);
  std::vector<int> getPoints(void);
  static int random(int lower, int upper);
  bool overlap(LineSeg& line);
  bool intersect(LineSeg& line);
  void printLineSeg(void);
  void setPoints(int a, int b, int c, int d);
  // bool validLength(int& a, int& b, int& c, int& d);

 private:
  float slope;
  float b;
  float x1;
  float y1;
  float x2;
  float y2;
  std::vector<int> points;
  // If this boolean is true, the slope is vertical.
  bool flag;
};

#endif
