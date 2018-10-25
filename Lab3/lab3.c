// Jack Weissenberger lab 3 Shell
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (){
  char *cmd = "";
  char *buffer = "";
  int pid;
  size_t bufsize = 32;
  size_t characters;
  int maxNumArgs = 30;
  char *args[maxNumArgs];

  printf("Note: please put a space at the end of your command\n");
  printf("Type a command with a space after it or type exit to exit:\n");
  while(1){


    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    //read in the inputted line
    characters = getline(&buffer,&bufsize,stdin);

    // if the user types exit, exit the program
    if (strcmp(buffer, "exit\n") == 0){
      printf("Exiting\n");
      break;
    }

    //tokenize the input on each of the spaces
    char *token;
    token = strtok(buffer, " ");
    int i = 0;

    int background = 0;
    while( token != NULL ) {
      // the first token is the command
      if (i == 0){
        cmd = token;
      }

      // the rest of the tokens are the command arguments
      else{
        // handel the case if there is an &
        if(strcmp(token, "&") == 0){
          background = 1;
        }
        args[i-1] = token;
      }


      token = strtok(NULL, " ");
      ++i;
    }
    // set the token after the last token to be null
    args[i-1] = NULL;

    // if there is an &
    if (background == 1){
      wait(NULL);
    }

    // fork for the new command
    else{
      pid = fork();
      if (pid ==0){
          if(execvp(cmd, args)){
            printf("You did not input a working command\n");
          }
      }
    }


  }

  exit(0);

}
