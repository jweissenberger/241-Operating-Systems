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

int main(int argc, char* argv[]) {

    if (argc==1) {
      printf("\nYou did not enter the number of stalls or the number of people into the command line\n");
      exit(1);
    }

    //int arg1 = atoi(argv[1]);
    int num_stalls = atoi(argv[1]);
    printf("Number of stalls: %d\n", num_stalls);
    int num_people = atoi(argv[2]);
    printf("Number of people: %d\n", num_people);

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

    int i = 0;
    char gender;
    int time;
    int time_arr[num_people];
    char gender_arr[num_people];

    while ((output = getline(&file_line, &num, pf)) != -1){
        if (i == 0){
          // Assuming the file is like how it is shown in the document
          // this line should show how many people are going to be waiting
        }

        else{
          time = file_line[0];
          gender = file_line[1];
          time_arr[i-1] = time-48;
          gender_arr[i-1] = gender;
        }
        ++i;
    }

    for (int j = 0; j < num_people; j++){
      printf("Gender: %c, time: %d\n", gender_arr[j], time_arr[j] );
    }

}

void quitHandler ( int theInt) {
  printf("\n Program terminated \n");
  exit(0);
}
