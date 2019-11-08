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

  while (true) {
    // Create streets with command line input.
    Streets streets(s_int,n_int,l_int,c_int);
    streets.generateStreetNames();
    std::cout.flush();
    // Output: a "name of street" (x1,y1) (x2,y2) for all streets.
    streets.printAddStreets();
    std::cout.flush();
    // Outputs "g".
    streets.printGraph();
    std::cout.flush();
    std::chrono::seconds timespan(streets.getNumWait());
    std::this_thread::sleep_for(timespan);
    streets.printRemoveStreets();
    std::cout.flush();

    // This code block makes it so if rgen is run on its own, EOF will terminate
    // the program.
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
