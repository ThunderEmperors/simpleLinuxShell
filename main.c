#include "main.h"

int main(int argc, char* argv[]){
  
  (void)argc, (void)argv;

  char* buf = NULL;
  size_t count = 0;
  ssize_t nread;

  while(1){
    write(STDOUT_FILENO, "MyShell$ ", 9);
  
    nread = getline(&buf, &count, stdin);

    if(nread == -1){
      perror("Quitting shell...");
      exit(1);
    }

    printf("%s", buf);

  }

  free(buf);
  return 0;

}