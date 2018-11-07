// Jack Weissenberger
// 241 Lab 3

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "ezipc.h"

int main(){

  FILE *pf;

  pf = fopen("/home/csuser/Lab5/test.txt", "r");

  int errnum;

  // error handeling for reading a file
  if(pf == NULL) {
      errnum = errno;
      fprintf(stderr, "Value of errno: %d\n", errno);
      perror("Error printed by perror");
      fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
  }

  int output;
  char *file_line; //getline allocates space
  file_line = NULL;
  unsigned long num; // number of chars from getline
  num= 0;


  while ((output = getline(&file_line, &num, pf)) != -1){
    if(file_line[20] == '\n'){
      printf("Yabooo\n");
    }
      //printf("20 letter: %c, strlen(): %d\n", file_line[20], strlen(file_line));
    }


}
