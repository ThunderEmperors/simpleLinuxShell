#ifndef MAIN_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

//support functions
char* read_input(void);
void tokenize_input(char* input_buffer, char* argArr[]);
void find_file_path(char* token, char* file);

#endif