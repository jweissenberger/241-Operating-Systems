// Jack Weissenberger
// Lab7 Unisex bathroom problem

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include "ezipc.h"

void quitHandler(int);

int main() {

    signal(SIGINT, quitHandler); //Set up quit handler

    FILE *pf;
    //location of file to read
    pf = fopen ("/home/csuser/Lab7/unisex.txt", "r");

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
    num = 0;
    char a;
    int num_stalls

    while ((output = getline(&file_line, &num, pf)) != -1){
        a = file_line[0];
        printf("%c \n", a);
    }

}

void quitHandler ( int theInt) {
  printf("\n Program terminated \n");
  exit(0);
}
