#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>



int main() {
    //open a text file named lab2.txt (be sure to include error handling)
    FILE *pf;
    int errnum;
    pf = fopen ("/home/csuser/Lab2/lab2.txt", "r");

    if(pf == NULL) {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
    }

    //create a process that will read and display each line of the file until the EOF is reached
    // and then exits
    int output;
    char *line ; //getline allocates space
    unsigned long num ; // number of chars from getline
    // in the line.
    unsigned int r ; // Saves the return value given by getline().
    line = NULL;
    num= 0;

    pid_t pid = fork();
    // s
    if (pid == 0) {
      while ((output = getline(&line, &num, pf)) != -1){
        printf("Process: %d, Line: %s",getpid() ,line);
      }
      exit(1);

    }
    //parent process case
    else {
      while ((output = getline(&line, &num, pf)) != -1){
        printf("Process: %d, Line: %s",getpid() ,line);
        }
        exit(1);
      }

    return 0;
}
