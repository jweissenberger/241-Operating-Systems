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

int male, female, inMale, inFemale, wait_BR;
int *M_in_BR;
int *F_in_BR;

int main(int argc, char* argv[]) {

    SETUP();

    if (argc==1) {
      printf("\nYou did not enter the number of stalls or the number of people into the command line\n");
      exit(1);
    }

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

    //Variables for File reading
    int output;
    char *file_line; //getline allocates space
    file_line = NULL;
    unsigned long num; // number of chars from getline
    num = 0;

    //variables that help read the information from the file
    int i = 0;
    char gender;
    int time;
    int time_arr[num_people];
    char gender_arr[num_people];

    // Semaphores and shared memory
    male = SEMAPHORE(SEM_BIN, 1);
    female = SEMAPHORE(SEM_BIN, 1);
    inMale = SEMAPHORE(SEM_BIN, 1);
    inFemale = SEMAPHORE(SEM_BIN, 1);
    M_in_BR = SHARED_MEMORY(10);
    F_in_BR = SHARED_MEMORY(10);
    wait_BR = SEMAPHORE(SEM_BIN, 0);

    *M_in_BR = 0;
    *F_in_BR = 0;
    int wait_time = 1;

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

    pid_t pid;

    for (int j = 0; j < num_people; j++){
      pid = fork();
      if (pid == 0){
        if (gender_arr[j] == 'M'){
          printf("A Man has entered\n");

          // the male function
          P(male);
            P(inMale);
            M_in_BR++; //increment the number of people in the bathroom
            if(M_in_BR == 1){
              P(wait_BR);
            }
            V(inMale);
              //critical section
              printf("Man %d is going to the bathroom\n", j);
              wait_time = j//((j + 1) * 3) % 4 + 1;
              wait(wait_time);
              printf("Man %d is leaving the bathroom\n", j);
            P(inMale);
            M_in_BR--;
            if(M_in_BR == 0){
              V(wait_BR);
                if(F_in_BR == 0){
                  V(male);
                }
            }
            V(inMale);
            V(female);

        }
        if (gender_arr[j] == 'F'){
          printf("A Woman has entered\n");
          // the woman function

          P(female);
            P(inFemale);
            F_in_BR++; //increment the number of people in the bathroom
            if(F_in_BR == 1){
              P(wait_BR);
            }
            V(inFemale);
              //critical section
              printf("Woman %d is going to the bathroom\n", j);
              wait_time = j;//((j + 1) * 3) % 4 + 1;
              wait(wait_time);
              printf("Woman %d is leaving the bathroom\n", j);
            P(inFemale);
            F_in_BR--;
            if(F_in_BR == 0){
              V(wait_BR);
                if(M_in_BR == 0){
                  V(female);
                }
            }
            V(inFemale);
            V(male);
        }
      }
    }

    while(wait(&signal)!=-1); // wait for all child processes to end
    return 0;

}

void quitHandler ( int theInt) {
  printf("\n Program terminated \n");
  exit(0);
}
