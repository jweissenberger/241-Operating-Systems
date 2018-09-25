#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

// Prototypes
void alarmHandler(int);
void quitHandler(int);

int main (int argc, char* argv[]) {

  // checking to see if no word was entered
  if (argc==1) {
    printf("\n No word was entered\n");
    exit(1);
  }

  // checking if more than one word was entered
  if (argc>2) {
    printf("\n You entered more than one word, please re-try the program with one word\n");
    exit(1);
  }

  char* word = argv[1];
  printf("The word: %s\n",  word);

  printf("%c is the first letter of the word\n", word[0]);

  // set signal handlers
  signal ( SIGALRM, alarmHandler);
  signal ( SIGINT, quitHandler );

  // measure the length of the string
  int k = 0;
  for (int j = 0; word[j] != '\0' ; j++) {
    k = j;
  }
  k++;
  printf("%d\n", k);

  //make an array that's the same length as the input string and fill it with
  // blanks that can be filled in during the next for loop

  char* letters[k];

  for (int i = 0; word[i] != '\0' ; i++) {
      alarm(5);

      printf("%c, %d\n", word[i], i);
      pause();
  }

  return 0;

}

void alarmHandler( int theAlarm ) {
  printf("\n Took too long, now revealing a letter \n");
  return;
}

void quitHandler ( int theInt) {
  printf("\n Quitting!\n");
  exit(3);
}
