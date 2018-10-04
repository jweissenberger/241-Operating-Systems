//Jack Weissenberger Lab1

/*
1.) Explain one of the fundamental differences between signal() and sigaction() system calls:

One of the biggest differences is that sigaction is able to block different signals until
the initial handler returns whereas signal usually does not block other signals

2.) What is the purpose of SIGKILL if it cannot be intercepted?

SIGKILL is used as a last resort by operating systems. The most common example
I have found for the use of SIGKILL is that sometimes in operating system
shutdown, if the procedures do not want to exit, the system will call SIGKILL
which cannot be intercepted and can help speed up shutdown.

*/
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

// Prototypes
void alarmHandler(int);
void quitHandler(int);
void zHandler(int);

#define MAX 20

//global variables
int foundLetter = 0;
int finishedWord = 0;
int randNum;
char buf[MAX];
char wordArray[100];
int len;
char* word;


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

  // get the inputted word from the command line
  word = argv[1];

  // set signal handlers
  signal ( SIGALRM, alarmHandler );
  signal ( SIGINT, quitHandler );
  signal ( SIGTSTP, zHandler );

  // measure the length of the string
  len = 0;
  for (int j = 0; word[j] != '\0' ; j++) {
    len = j;
  }
  len++;

  //fill word array with _ so that the right letters can be filled later
  for (int u = 0; u < len;  u++) {
    wordArray[u] = '_';
  }



  // This will keep iterating until the entire word is complete
  // It will return the same string if the user guesses a letter that has already been guessed
  while(finishedWord == 0) {

      alarm(10);

      printf("\nGuess a character in the word: \n");
      fgets(buf, MAX, stdin);

      foundLetter = 0; // this is 0 if the guessed letter has not been found and 1 if it has

      //check if the letter is in the word
      for (int p = 0; p < len; p++){

        // if the guessed letter matches one of the letters of the word
        if (word[p] == buf[0]){
          printf("The letter is in the word\n");
          wordArray[p] = buf[0];
          printf("Word: %s\n", wordArray);
          foundLetter = 1;
        }
        // if the guessed letter doesn't match one of the letters of the word
        if ((word[p] != buf[0]) && (p == (len-1)) && (foundLetter == 0)){
          system("clear\0");

          printf("\n The letter is not in the word, here is a hint\n");

          //randomly show a new letter
          randNum = rand() % len;
          // check to make sure that this letter has not been revealed yet
          while (wordArray[randNum] != '_'){
            randNum = rand() % len;
          }
          wordArray[randNum] = word[randNum];
          printf("Word: %s\n", wordArray);
        }
      }
    alarm(0);

    // check to see if the entire word has been guessed
    // this is necessary for cases when the word has many of the same letter
    for (int m = 0; m < len; m++){
      if (wordArray[m] == '_'){
        break;
      }
      if ((m == (len-1)) && (wordArray[m] != '_')){
        finishedWord = 1;
      }
    }

  }

  printf("\nYou're done!\n");
  return 0;

}

// cheat mode with control Z to check reveal a hidden letter
void zHandler(int theLetter){
  printf("\nI will now reveal a letter...");
  randNum = rand() % len;
  while (wordArray[randNum] != '_'){
    randNum = rand() % len;
  }
  printf("\n%c\n", word[randNum]);
  return;
}

void alarmHandler( int theAlarm ) {
  printf("\n You took too long \n");
  return;
}


void quitHandler ( int theInt) {
  printf("\n Quitting!\n");
  exit(3);
}
