// Jack Weissenberger Lab 4

#include "ezipc.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int room, chairs, barber, m, cash, chair_ptr;
char *available_seats;
void quitHandler(int);
void customer(int id);

int main(){

  SETUP(); // sets up the semaphores

  signal ( SIGINT, quitHandler );

  available_seats = SHARED_MEMORY(2);

  int customers;
  int finish;
  // ask for number of chairs
  printf("Please enter the number of chairs\n");
  scanf("%d", &chairs);
  // ask for number of customers
  printf("Please enter the number of customers\n");
  scanf("%d", &customers);

  printf("Number of chairs: %d, Number of customers: %d\n", chairs, customers);

  chair_ptr = *available_seats;
  *available_seats = chairs;

  room = SEMAPHORE(SEM_CNT, chairs);
  cash = SEMAPHORE(SEM_BIN, 1);
  barber = SEMAPHORE(SEM_BIN, 0);
  m = SEMAPHORE(SEM_BIN, 0); // this is for the mutual exclusion

  pid_t barber_pid = getpid();
  printf("Barber process ID: %d\n", barber_pid);
  printf("here\n");
  for (int i = 0; i < customers; i++){

    pid_t pid = fork();
    sleep(rand()%10);

    if (pid == 0){
      customer(i);
    }

  }


  //this is the barber sleeping
  while(1){
    P(barber); // this requests the barber, waking him up
    P(m); // for the mutual exclusion, so that only you specifially are using
    // the barber
    sleep(rand()%10);
    V(m);
    V(room);

    // need to create a control z handler to exit, look at the poject, you also
    // need to print something out when you type control z
  }

  while(wait(&finish) != 1); // wait for all of the child processes

  return 0;
}


void customer(int id){

  printf("In customer\n" );
  printf("available_seats: %d\n", (int)available_seats[0] );
  if (available_seats > 0){
    printf("there is a seat available\n" );
  }

  //request the room
  P(room);
  P(m);

  available_seats[0] = (int)available_seats[0] - 1;
  printf("Customer %d arrived, %d many seats remaining %d \n", id, (int)available_seats[0] );

  //update everything

  V(m);

  //now wake up the barber, convert him to 0 from negative one
  V(barber);

  printf("Getting a haircut\n" );
  // wait random time for while you are getting the haircut

  P(cash);
  // wait a random time at the cashier
  V(cash);
  exit(0);
}

void quitHandler ( int theInt) {
  printf("\n Quitting!\n");
  exit(3);
}
