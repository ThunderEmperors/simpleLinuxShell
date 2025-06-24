#include "main.h"

char* read_input(void){
  char* input_buffer = NULL;
  size_t count = 0;
  ssize_t nread;

  nread = getline(&input_buffer, &count, stdin);

  if(nread == -1){
    free(input_buffer);
    exit(0);
  }

  return input_buffer;

}

void tokenize_input(char* input_buffer, char* argArr[]){

  char* token;
  int idx;

  char* file = malloc(sizeof(char)* 100);

  token = strtok(input_buffer, " \n");

  idx = 0;

  while(token){
    if(idx == 0){
      find_file_path(token, file);
      argArr[idx] = file;
      // printf("%s", argArr[0]);
    } else{
      argArr[idx] = token;
    }

    // argArr[idx] = token;
    token = strtok(NULL, " \n");
    idx++;
  }
  argArr[idx] = NULL;

}

void find_file_path(char* token, char* path){

  int mypipe[2];
  if(pipe(mypipe) == -1){
    perror("pipe could not be created");
    exit(1);
  }

  pid_t pid = fork();

  if(pid == -1){
    perror("file finding path could not be forked");
    exit(1);
  }
  else if(pid == 0){
    close(STDOUT_FILENO);
    dup(mypipe[1]);
    close(mypipe[0]);

    char* exec_command[] = { "which", token, 0};

    execvp(exec_command[0], exec_command);

    perror("error in execvp command for finding file path");
    exit(1);
  }

  close(mypipe[1]);

  ssize_t bytesRead = read(mypipe[0], path, 100);
  if(bytesRead > 0){
    path[bytesRead-1] = '\0';
  } else {
    path[0] = '\0';
  }

  close(mypipe[0]);
  wait(NULL);
}