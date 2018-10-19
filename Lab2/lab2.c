//Jack Weissenberger
//241 Lab 2

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {

    FILE *pf;
    //location of file to read
    pf = fopen ("/home/csuser/Lab2/lab2.txt", "r");

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

    pid_t pid = fork();
    // child process case
    if (pid == 0) {
      while ((output = getline(&file_line, &num, pf)) != -1){
        printf("Process: %d, Line: %s",getpid() ,file_line);
      }
      exit(1);

    }
    //parent process case
    else {
      while ((output = getline(&file_line, &num, pf)) != -1){
        printf("Process: %d, Line: %s",getpid() ,file_line);
        }
        exit(1);
      }

    return 0;
}
