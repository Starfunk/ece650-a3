#ifndef STREETS_H
#define STREETS_H

class Streets {
 public:
  Streets();
  Streets(int num_streets=5, int num_segments=5, int num_wait=5, int num_range=20);
  bool checkOverlap(Street street);
  void printAddStreets(void);
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
  int num_segments;
  int num_range;
  int num_wait;
};

#endif
