#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <sys/poll.h>
#include "headers/lineseg.h"
#include "headers/street.h"
#include "headers/streets.h"

int main(int argc, char** argv) {
  std::string s_str, n_str, l_str, c_str;
  int s_int, n_int, l_int, c_int;
  bool s_flag = false;
  bool n_flag = false;
  bool l_flag = false;
  bool c_flag = false;

  // Put command line arguments into the vector, argvector.
  std::vector<std::string> argvector;
  for (char * c = *argv; c; c=*++argv) {
    argvector.push_back(c);
  }

  // for (int i = 0; i < argvector.size(); i++) {
  //   std::cout << argvector[i] << "\n";
  // }

 /*
  * Potential for error: if letter is missing a number value, then
  * the call argvector[i+1] could get access to memory I don't want it to
  * have access to.
  */
  for (int i = 0; i < argvector.size(); i++) {
    if (argvector[i] == "-s") {
      s_flag = true;
      s_str = argvector[i+1];
      s_int = atoi(s_str.c_str());
    }
    if (argvector[i] == "-n") {
      n_flag = true;
      n_str = argvector[i+1];
      n_int = atoi(n_str.c_str());
    }
    if (argvector[i] == "-l") {
      l_flag = true;
      l_str = argvector[i+1];
      l_int = atoi(l_str.c_str());
    }
    if (argvector[i] == "-c") {
      c_flag = true;
      c_str = argvector[i+1];
      c_int = atoi(c_str.c_str());
    }
  }

  // std::cout << "s_flag: " << s_flag << "\n";
  // std::cout << "s_int: " << s_int << "\n";
  // If argument was omitted, set to default.
  if (s_flag == false) {
    s_int = 10;
  }
  if (n_flag == false) {
    n_int = 5;
  }
  if (l_flag == false) {
    l_int = 5;
  }
  if (c_flag == false) {
    c_int = 20;
  }

  // std::cout << "s_flag: " << s_flag << "\n";
  // std::cout << "s_int: " << s_int << "\n";
  // std::cout << "n_flag: " << n_flag << "\n";
  // std::cout << "n_int: " << n_int << "\n";
  // std::cout << "l_flag: " << l_flag << "\n";
  // std::cout << "l_int: " << l_int << "\n";
  // std::cout << "c_flag: " << c_flag << "\n";
  // std::cout << "c_int: " << c_int << "\n";

  // LineSeg l1(12,-20,-12,17);
  // LineSeg l2(12,-20,-12,17);

  // LineSeg l1(3,-16,-17,2);
  // LineSeg l2(3,-16,-17,2);

  // LineSeg l1(-17,2,-15,-1);
  // LineSeg l2(-17,2,-15,-1);

  // LineSeg l1(-15,-1,-14,-18);
  // LineSeg l2(-15,-1,-14,-18);

  // LineSeg l1(-15,-1,-14,-18);
  // LineSeg l2(-14,-18,2,-19);
  // bool t = l1.intersect(l2);
  // std::cout << t << "\n";
  // LineSeg l3(13,-1,-2,-3);
  // LineSeg l4(-2,-3,5,7);
  // bool f = l3.intersect(l4);
  // std::cout << f << "\n";
  // exit(1);
  //
  // LineSeg l1(1,1,2,3);
  // LineSeg l2(2,3,-6,1);
  //
  // LineSeg l1(12,-20,-12,17);
  // LineSeg l2(-12,17,2,7);
  //
  // std::cout << "Example of overlap: " << l1.overlap(l2) << "\n";
  // std::cout << "Example of no intersection: " << l1.intersect(l2) << "\n";
  //
  // std::cout << "Example of overlap: " << l2.overlap(l1) << "\n";
  // std::cout << "Example of no intersection: " << l4.intersect(l3) << "\n";

  // // TESTING STREETS:
  // Street street(10, 5);
  // for (LineSeg lineseg : street.getLineSegs()) {
  //   lineseg.printLineSeg();
  // }
  // street.printCoords();


  while (true) {
    // Create streets with command line input.
    Streets streets(s_int,n_int,l_int,c_int);
    streets.generateStreetNames();
    std::cout.flush();
    // Outputs a "name of street" (x1,y1) (x2,y2) for all streets.
    streets.printAddStreets();
    // streets.printAddStreetsCerr();
    std::cout.flush();
    // Outputs "g".
    streets.printGraph();
    std::cout.flush();
    std::chrono::seconds timespan(streets.getNumWait());
    std::this_thread::sleep_for(timespan);
    streets.printRemoveStreets();
    std::cout.flush();

    struct pollfd fds;
        int ret;
        fds.fd = 0; /* this is STDIN */
        fds.events = POLLIN;
        ret = poll(&fds, 1, 0);
        if(ret == 1) {
          std::string line;
          std::getline(std::cin, line);
          if (std::cin.eof()) {
            break;
          }
          else {
            continue;
          }
        }
  }
  return 0;
}
