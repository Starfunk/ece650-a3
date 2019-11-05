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
        if (std::cin.eof()) {
          break;
        }
        std::cout << line << std::endl;
        std::cout.flush();
    }
    // std::cout << "[B] saw EOF" << std::endl;
    return 0;
}

int main (int argc, char **argv) {
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
      dup2(RGENtoA1[0], STDIN_FILENO);
      close(RGENtoA1[0]);
      close(RGENtoA1[1]);

      dup2(A1toA2[1], STDOUT_FILENO);
      close(A1toA2[0]);
      close(A1toA2[1]);

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
  pid_t rgen = child_pid;
  if (child_pid == 0) {
    // redirect stdout to the pipe
        dup2(RGENtoA1[1], STDOUT_FILENO);
        close(RGENtoA1[0]);
        close(RGENtoA1[1]);     // Close this too!

        int rgen = execv("rgen",argv);

        // if (rgen == 1) {
        //   for (pid_t k : kids) {
        //       int status;
        //       kill (k, SIGTERM);
        //       waitpid(k, &status, 0);
        //   }
        // }

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

    //UNCOMMENT THIS! THIS IS IMPORTANT!
  // dup2(A1toA2[1], STDOUT_FILENO);
  // close(A1toA2[0]);
  // close(A1toA2[1]);

  child_pid = fork();
  if (child_pid == 0) {
    // redirect stdout to the pipe
        dup2(A1toA2[1], STDOUT_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);
        int you = procB();
        return you;
  }
  else if (child_pid < 0) {
       std::cerr << "Error: could not fork rgen\n";
       return 1;
   }
   kids.push_back(child_pid);

  int status;
  waitpid(-1,&status,0);
  for (pid_t k : kids) {
      int status;
      kill (k, SIGTERM);
      waitpid(k, &status, 0);
  }

    return 0;
}
