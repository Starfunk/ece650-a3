#include<vector>
#include <unistd.h>
#include <signal.h>
#include<iostream>
#include <thread>
#include <chrono>


int procB(void) {
    // Process B writing to C
    while (!std::cin.eof()) {
        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);
        std::cout << line << std::endl;
        std::cout.flush();
    }
    std::cout << "[B] saw EOF" << std::endl;
    return 0;
}

int main (int argc, char **argv) {
  char s[5000];
  std::vector<pid_t> kids;

  // Initialize pipe from Rgen to A1
  int RGENtoA1[2];
  pipe(RGENtoA1);
  pid_t child_pid;

  // Initialize pipe from A1 to A2
  int A1toA2[2];
  pipe(A1toA2);

  int A1toA3[2];
  pipe(A1toA3);


  // Start A1 program
  child_pid = fork();
  if(child_pid == 0)
  {
      std::cout << "WE IN PYTHON CHILD\n";
      dup2(RGENtoA1[0], STDIN_FILENO);
      close(RGENtoA1[0]);
      close(RGENtoA1[1]);

      dup2(A1toA2[1], STDOUT_FILENO);
      close(A1toA2[0]);
      close(A1toA2[1]);

      // dup2(A1toA3[1], STDOUT_FILENO);
      // close(A1toA3[0]);
      // close(A1toA3[1]);



      // dup2(A1toOUT[1], STDOUT_FILENO);
      // close(A1toA2[0]);
      // close(A1toA2[1]);


      char *argv1[3];

      argv1[0] = (char *)"python";
      argv1[1] = (char *)"ece650-a1.py";
      argv1[2] = nullptr;

      return execvp("python", argv1);
  }
  else if (child_pid < 0) {
       std::cerr << "Error: could not fork\n";
       return 1;
   }
  kids.push_back(child_pid);

  child_pid = fork();
  if (child_pid == 0) {
    // redirect stdout to the pipe
        std::cout << "WE IN RGEN CHILD\n";
        dup2(RGENtoA1[1], STDOUT_FILENO);
        close(RGENtoA1[0]);
        close(RGENtoA1[1]);     // Close this too!

        int rgen = execv("rgen",argv);
        return rgen;
  }
  else if (child_pid < 0) {
       std::cerr << "Error: could not fork rgen\n";
       return 1;
   }
   kids.push_back(child_pid);

   child_pid = fork();
   if (child_pid == 0) {
     // redirect stdout to the pipe
         std::cout << "WE IN A2 CHILD\n";
         dup2(A1toA2[0], STDIN_FILENO);
         close(A1toA2[0]);
         close(A1toA2[1]);     // Close this too!

         int a2 = execv("ece650-a2",argv);
         return a2;
   }
   else if (child_pid < 0) {
        std::cerr << "Error: could not fork rgen\n";
        return 1;
    }
    kids.push_back(child_pid);

    // Starts a process that lets us see output from A1
    child_pid = fork();
    if (child_pid == 0) {

      // dup2(A1toA3[0], STDIN_FILENO);
      // close(A1toA3[0]);
      // close(A1toA3[1]);
      // redirect stdout to the pipe
      // THIS seems to work, if this is on then we can see the output of A1's program
      dup2(A1toA2[0], STDIN_FILENO);
      close(A1toA2[0]);
      close(A1toA2[1]);
      // while (!std::cin.eof()) {
      //     // read a line of input until EOL and store in a string
      //     std::string line;
      //     std::getline(std::cin, line);
      //     std::cout << "WE ARE IN A1's reading process" <<line << std::endl;
      //     std::cout.flush();
      // }
    }
    else if (child_pid < 0) {
         std::cerr << "Error: could not fork rgen\n";
         return 1;
     }
     kids.push_back(child_pid);

  dup2(A1toA2[1], STDOUT_FILENO);
  close(A1toA2[0]);
  close(A1toA2[1]);

  int you = procB();


  pid_t wpid;
  int status = 0;
  while ((wpid = wait(&status)) > 0);
  // send kill signal to all children
  for (pid_t k : kids) {
      int status;
      kill (k, SIGTERM);
      waitpid(k, &status, 0);
  }

  //
  //   std::cout << "WE GET TO END OF ECE A3\n";
  //   //
  //   // std::cout << "Replace with your solution for the main "
  //   //           << "driver program of Assignment 3\n";

    return 0;
}
