#ifndef STREET_H
#define STREET_H

class Street {
 public:
  Street();
  Street(int range, int segments);
  void printCoords(void);
  std::vector<LineSeg> getLineSegs(void);
  std::vector<int> getCoords(void);
  bool checkValid(LineSeg& lineseg);


 private:
  // std::vector<int> coordinates;
  std::vector<LineSeg> linesegs;
  std::vector<int> coords;
};

#endif
