#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include "headers/lineseg.h"
#include "headers/street.h"
#include "headers/streets.h"


int main(int argc, char** argv) {



  // std::cout << "We IN RGEN\n";

  // First is number of streets, second is number of line segments, third is
  // number of
  while (true) {
    // std::chrono::seconds timespan1(4); // or whatever
    // std::this_thread::sleep_for(timespan1);
    Streets streets(5,5,10);
    streets.generateStreetNames();
    std::cout.flush();
    streets.printAddStreets();
    std::cout.flush();
    streets.printGraph();
    std::cout.flush();
    std::chrono::seconds timespan(10); // or whatever
    std::this_thread::sleep_for(timespan);
    streets.printRemoveStreets();
    std::cout.flush();
  }







  // Street street1(-10,10,10);
  //
  // street1.printCoords();



  // LineSeg lne(0,3,2,-20);
  // LineSeg lne2(2,-20,-1,-2);
  //
  // lne.printLineSeg();
  // lne2.printLineSeg();
  //
  //
  // std::cout << lne.intersect(lne2);


  // int arg;
  // std::string s_str, n_str, l_str, c_str;
  // int s_int, n_int, l_int, c_int;
  //
  // while ((arg = getopt(argc, argv, "s:n:l:c:")) != -1) {
  //   switch(arg) {
  //     case 's':
  //       s_str= optarg;
  //       s_int = atoi(s_str.c_str());
  //       if (s_int < 2) {
  //         std::cerr << "Error: the argument for s must be greater than 2.\n";
  //         exit(1);
  //       }
  //       break;
  //     case 'n':
  //       n_str = optarg;
  //       n_int = atoi(n_str.c_str());
  //       if (n_int < 1) {
  //         std::cerr << "Error: the argument for n must be greater than 1.\n";
  //         exit(1);
  //       }
  //       break;
  //     case 'l':
  //       l_str = optarg;
  //       l_int = atoi(l_str.c_str());
  //       if (l_int < 5) {
  //         std::cerr << "Error: the argument for l must be greater than 5.\n";
  //         exit(1);
  //       }
  //       break;
  //     case 'c':
  //       c_str = optarg;
  //       c_int = atoi(c_str.c_str());
  //       if (c_int < 1) {
  //         std::cerr << "Error: the argument for c must be greater than 1.\n";
  //         exit(1);
  //       }
  //       break;
  //     case '?':
  //       std::cerr << "Error: incorrect input\n";
  //       break;
  //   }
  // }
  // std::cout << s_str<< "\n";
  // std::cout << n_str << "\n";
  // std::cout << l_str << "\n";
  // std::cout << c_str << "\n";

  return 0;

}
