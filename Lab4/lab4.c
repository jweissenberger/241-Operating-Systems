// Jack Weissenberger, 11/1/2018
// Operating Systems, Lab 4, The Sleeping Barber problem

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include "ezipc.h"


int num_chairs, max_customers,
int randTime;
int chair_sem, barber, m, cash;
int* room;

void customer(int id);
void quitHandler(int);


int main(int argc, char *argv[]) {
    pid_t pid;

    // set up the quitHandler
    signal(SIGINT, quitHandler);

    // set up everything for the semaphores and shared memory
    SETUP();

    if(argc!=3){
        printf("Input error, please put the number of chairs followed by the number of customers as a command line argument\n");
        exit(-1);
    }

    else{
        printf("Barber Process id: %d\nKill barber process with: kill -USR1 %d\n",getpid(),getpid());
        printf("Num Chairs: %s\nMax-Customers:%s\n",argv[1], argv[2]);

        num_chairs = strtol(argv[1],NULL,0);
        max_customers = strtol(argv[2],NULL,0);

        room = SHARED_MEMORY(20); // for the people in the room
        m = SEMAPHORE(SEM_BIN, 1); // mutex
        cash = SEMAPHORE(SEM_BIN, 1); // for the person waiting at the cashier
        chair_sem = SEMAPHORE(SEM_CNT, num_chairs);
        barber = SEMAPHORE(SEM_BIN, 1);
        *room=num_chairs;


        printf("%d\n", num_chairs);
    }

    srand(time(NULL));
    randTime=rand()%5;
    for(int i=1;i<=max_customers;i++){
        pid=fork();
        sleep(randTime);
        if(pid==0){
            printf("I am customer %d\n",i);
            customer(i);
            return 0;
        }

    }

    //this is the barber sleeping
    while(1){
      P(barber); // this requests the barber, waking him up
      P(m); // for the mutual exclusion, so that only you specifially are using
      // the barber
      sleep(rand()%10);
      V(m);

    }

    return 0;
}

void customer(int id){
    P(m);
    if(*room <= 0){
        printf("Customer %d Left because no chairs were available\n", id);
    }
    else{
        printf("Customer %d Arrived, %d chairs left\n",id, --*room);
    }
    V(m);

    P(barber);
    P(m);
    printf("Barber awakened, there is/are %d seats available\n",++*room);
    V(m);
    printf("**************Haircut: Customer %d is getting a haircut\n", id);
    sleep(rand()%5);
    V(barber);

    // go to the cashier
    P(cash);
    printf("Customer %d is paying at the cashier\n", id);
    sleep(rand()%5);
    V(cash);
    printf("Customer %d has paid the cashier\n", id);
}

void quitHandler ( int theInt) {
  printf("\n DONE!\n");
  printf("Close shop and go home\n" );
  exit(3);
}
