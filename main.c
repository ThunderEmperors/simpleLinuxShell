#include "main.h"

int main(int argc, char* argv[]){
  
  (void)argc, (void)argv;

  char* buf;
  pid_t child_pid;
  int status;

  while(1){
    write(STDOUT_FILENO, "MyShell$ ", 9);
  
    buf = read_input();
    char** argArr = tokenize_input(buf);

    child_pid = fork();

    if(child_pid == -1){
      perror("Couldn't create child process");
      exit(41);
    }

    if(child_pid == 0){
      if(execve(argArr[0], argArr, NULL) == -1){
        perror("execve couldn't execute.");
        exit(7);
      }
    } else {
      wait(&status);
    }

  }

  free(buf);
  return 0;

}