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

char** tokenize_input(char* input_buffer){

  char* token;
  char** argArr;
  int idx;

  token = strtok(input_buffer, " \n");

  // printf("%s", find_file_path(token));

  argArr = malloc(sizeof(char *) * 1024);
  idx = 0;

  while(token){
    // printf("%s", token);
    // if(idx == 0){
    //   argArr[idx] = find_file_path(token);
    // } else{
    //   argArr[idx] = token;
    // }
    argArr[idx] = token;
    token = strtok(NULL, " \n");
    idx++;
  }
  argArr[idx] = NULL;

  return argArr;

}

/*

char* find_file_path(char* token){

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
  char buf[100];
  read(mypipe[0], buf, sizeof(buf));



  return buf;
  
}

*/