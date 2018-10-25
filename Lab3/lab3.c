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

  printf("Type a command with a space after it or type exit to exit: ");
  while(1){


    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }


    characters = getline(&buffer,&bufsize,stdin);

    if (strcmp(buffer, "exit\n") == 0){
      printf("Exiting\n");
      break;
    }

    char *token;
    token = strtok(buffer, " ");
    int i = 0;

    int background = 0;
    while( token != NULL ) {
      if (i == 0){
        cmd = token;
      }
      else{
        if(strcmp(token, "&") == 0){
          background = 1;
        }
        args[i-1] = token;
      }


      token = strtok(NULL, " ");
      ++i;
    }
    args[i-1] = NULL;

    if (background == 1){
      wait(NULL);
    }
    else{
      pid = fork();
      if (pid ==0){
          execvp(cmd, args);
      }
    }


  }

  exit(0);

}
