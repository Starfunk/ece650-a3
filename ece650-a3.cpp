#include <vector>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <thread>
#include <chrono>

// This function is used in a child process to parse input from the terminal
// and send the input to A2.
int parseinput(void) {
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
    return 0;
}

int main (int argc, char **argv) {
  std::vector<pid_t> kids;
  pid_t child_pid;
  // Initialize pipe from Rgen to A1
  int RGENtoA1[2];
  pipe(RGENtoA1);
  // Initialize pipe from A1 to A2
  int A1toA2[2];
  pipe(A1toA2);
  // Initialize pipe from A1 to A3
  int A1toA3[2];
  pipe(A1toA3);
  // Start A1 program
  child_pid = fork();
  if (child_pid == 0) {
      // Redirect A1's stdin to pipe connected to rgens stdout.
      dup2(RGENtoA1[0], STDIN_FILENO);
      close(RGENtoA1[0]);
      close(RGENtoA1[1]);
      // Redirect A1's stdout to pipe connected to A2's stdin.
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
  if (child_pid == 0) {
        // Redirect stdout from rgen to the pipe connected to A1.
        dup2(RGENtoA1[1], STDOUT_FILENO);
        close(RGENtoA1[0]);
        close(RGENtoA1[1]);
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
         // Redirect stdin for A2 to the read end of the pipe, A1toA2.
         dup2(A1toA2[0], STDIN_FILENO);
         close(A1toA2[0]);
         close(A1toA2[1]);
         int a2 = execv("ece650-a2",argv);
         return a2;
   }
   else if (child_pid < 0) {
        std::cerr << "Error: could not fork rgen\n";
        return 1;
    }
    kids.push_back(child_pid);

  child_pid = fork();
  if (child_pid == 0) {
        // Redirect stdout from driver to pipe connected to A2.
        dup2(A1toA2[1], STDOUT_FILENO);
        close(A1toA2[0]);
        close(A1toA2[1]);
        int parse = parseinput();
        return parse;
  }
  else if (child_pid < 0) {
       std::cerr << "Error: could not fork rgen\n";
       return 1;
   }
   kids.push_back(child_pid);

 /*
  * waitpid with the argument -1 waits for any child process of the
  * parent to terminate and then terminates the remaining child processes.
  * This way, if rgen errors out, the remaining child processes will
  * also shut down
  */
  int status;
  waitpid(-1,&status,0);
  for (pid_t k : kids) {
      int status;
      kill (k, SIGTERM);
      waitpid(k, &status, 0);
  }
    return 0;
}
