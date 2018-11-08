// Jack Weissenberger
// 241 Lab 5

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include "ezipc.h"

void quitHandler(int);

int SM_sem1, SM_sem2;
int SM1_full, SM2_full;
int SM1_empty, SM2_empty;
char *SM1, *SM2;


int main() {

    signal(SIGINT, quitHandler);

    SETUP();

    SM_sem1=SEMAPHORE(SEM_BIN, 1); // semaphore for SM1
    SM_sem2=SEMAPHORE(SEM_BIN, 1); // semaphore for SM2
    SM1_full=SEMAPHORE(SEM_BIN,0); // semaphore to check if SM1 is full
    SM2_full=SEMAPHORE(SEM_BIN,0); // semaphore to check if SM2 is full
    SM1_empty=SEMAPHORE(SEM_BIN,1); // semaphore to check if SM1 is empty
    SM2_empty=SEMAPHORE(SEM_BIN,1); // semaphore to check if SM2 is empty
    SM1=SHARED_MEMORY(1); // shared memory between producer and squasher
    SM2=SHARED_MEMORY(1); // shared memory between squasher and printer

    int signal;
    pid_t pid;
    pid=fork();
    if (pid==0){
        pid=fork();
        if(pid==0){
            //produce
            FILE *pf;
            //file location of the test file, this will change based on user
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
            char *char_line; //getline allocates space
            char_line = NULL;
            unsigned long num; // number of chars from getline
            num= 0;

            while((output = getline(&char_line, &num, pf)) != -1){

              strcpy(char_line,strtok(char_line,"\n"));
              strcat(char_line,"<EOL>"); // EOL to the end of the inputted line

                //iterate over the new line and put each of the chars one by one
                //into the shared memory
                for(int i=0;i<25;i++){
                    P(SM1_empty);
                    P(SM_sem1);
                    *SM1=char_line[i];
                    V(SM_sem1);
                    V(SM1_full);
                }
            }

        }
        else{
            //squash
            int prev = 0;// 1 if the previous input is *
            char from_sm; // the character from SM1
            while(1){
                // read from SM1
                P(SM1_full);
                P(SM_sem1);
                from_sm = *SM1;
                V(SM_sem1);
                V(SM1_empty);

                // check if *
                if(from_sm=='*'){
                    // case where current and previous were *
                    if(prev == 1){
                        P(SM2_empty);
                        P(SM_sem2);
                        *SM2='#';
                        V(SM_sem2);
                        V(SM2_full);
                        prev--;
                    }
                    // case where current is * but previous was not
                    else{
                        prev++;
                    }
                }

                // character is not a *
                else{
                    //case where previous was * but this one is not so need to
                    // print *
                    if (prev == 1){
                        P(SM2_empty);
                        P(SM_sem2);
                        *SM2='*';
                        V(SM_sem2);
                        V(SM2_full);
                        prev--;
                    }

                    // give the printer the current char (after the * if case above)
                    P(SM2_empty);
                    P(SM_sem2);
                    *SM2=from_sm;
                    V(SM_sem2);
                    V(SM2_full);
                }
            }
        }
    }


    //printer
    char output;
    while(1){
        // print out the characters one by one from the second shared memory
        for(int i=0;i<25;i++){
            P(SM2_full);
            P(SM_sem2);
            output = *SM2;
            V(SM_sem2);
            V(SM2_empty);
            printf("%c", output);
        }
        printf("%s\n"); // print a new line after every 25 characters
    }


    while(wait(&signal)!=-1); // wiat for all child processes to end
    return 0;

}

void quitHandler ( int theInt) {
  printf("\n Quitting\n");
  exit(0);
}
