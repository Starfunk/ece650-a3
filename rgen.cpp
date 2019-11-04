#include <algorithm>
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

int defaultv(int counter) {
  if (counter == 0) {
    return 10;
  }
  else if (counter == 1) {
    return 5;
  }
  else if (counter == 2) {
    return 5;
  }
  else if (counter == 3) {
    return 20;
  }
  else {
    std::cerr << "There should only be four command line arguments!\n";
    return 10;
  }
}

int main(int argc, char** argv) {

  int arg;
  std::string s_str, n_str, l_str, c_str;
  int s_int, n_int, l_int, c_int;
  int counter = 0;
  // std::cout << argv[0] << std::endl;
  // std::cout << argv[1] << std::endl;
  // std::cout << argv[2] << std::endl;
  bool s_flag = false;
  bool n_flag = false;
  bool l_flag = false;
  bool c_flag = false;

  std::vector<std::string> argvector;
  for (char * c = *argv; c; c=*++argv) {
    std::cout << c << "\n";
    argvector.push_back(c);
  }

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
  // std::cout << "ARGVECTOR SIZE: " << argvector.size() << "\n";

// char *foo = std::find(std::begin(argv), std::end(argv), s_command);
// // When the element is not found, std::find returns the end of the range
// if (foo != std::end(argv)) {
//     std::cerr << "Found at position " << std::distance(argv, foo) << std::endl;
// } else {
//     std::cerr << "Not found" << std::endl;
// }

  // if(std::find(argv.begin(), argv.end(), s_command) != v.end()) {
  //   std::cout << "HELLOWORLD\n";
  // }

  // std::cout << getopt(argc, argv, ":s:n:l:c:") << "\n";
  while ((arg = getopt(argc, argv, ":s:n:l:c:")) != -1) {
    switch(arg) {
      case 's':
        s_str= optarg;
        s_int = atoi(s_str.c_str());
        // if (s_int < 2) {
        //   std::cerr << "Error: the argument for s must be greater than 2.\n";
        //   exit(1);
        // }
        break;
      case 'n':
        n_str = optarg;
        n_int = atoi(n_str.c_str());
        // if (n_int < 1) {
        //   std::cerr << "Error: the argument for n must be greater than 1.\n";
        //   exit(1);
        // }
        break;
      case 'l':
        l_str = optarg;
        l_int = atoi(l_str.c_str());

        // if (l_int < 5) {
        //   std::cerr << "Error: the argument for l must be greater than 5.\n";
        //   exit(1);
        // }
        break;
      case 'c':
        c_str = optarg;
        c_int = atoi(c_str.c_str());
        // if (c_int < 1) {
        //   std::cerr << "Error: the argument for c must be greater than 1.\n";
        //   exit(1);
        // }
        break;
      case ':':
        std::cout << "this line is activating!\n";
        if (counter == 0) {
          s_int = defaultv(counter);
        }
        else if (counter == 1) {
          n_int = defaultv(counter);
        }
        else if (counter == 2) {
          l_int = defaultv(counter);
        }
        else if (counter == 3) {
          c_int = defaultv(counter);
        }
      case '?':
        std::cerr << "Error: incorrect input\n";
        break;
    }
    counter += 1;
  }

  while (true) {
    // std::chrono::seconds timespan1(4); // or whatever
    // std::this_thread::sleep_for(timespan1);
    Streets streets(s_int,n_int,l_int,c_int);
    streets.generateStreetNames();
    std::cout.flush();
    streets.printAddStreets();
    std::cout.flush();
    streets.printGraph();
    std::cout.flush();
    std::chrono::seconds timespan(streets.getNumWait()); // or whatever

    std::this_thread::sleep_for(timespan);
    streets.printRemoveStreets();
    std::cout.flush();
  }


  // std::cout << s_str<< "\n";
  // std::cout << n_str << "\n";
  // std::cout << l_str << "\n";
  // std::cout << c_str << "\n";

  return 0;

}
