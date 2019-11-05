#ifndef NODE_H
#define NODE_H

class Node {
 public:
  Node();
  Node(unsigned num1, std::vector<unsigned> vec);
  unsigned getId(void);
  std::vector<unsigned> getParentId(void);
  void printParentId(void);

 private:
  unsigned id;                      
  std::vector<unsigned> parent_id;
};

#endif
