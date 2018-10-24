// Jack Weissenberger lab 3 Shell
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (){
  char *cmd = "";
  char *buffer = "";

  printf("Type a command with a space after it: ");
  while(1){

    size_t bufsize = 32;
    size_t characters;

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

    int maxNumArgs = 30;
    char *args[maxNumArgs];

    int background = 0;
    while( token != NULL ) {
      if (i == 0){
        cmd = token;
      }
      else{
        //if
        args[i-1] = token;
      }

      //printf( " %s\n", token );

      token = strtok(NULL, " ");
      ++i;
    }
    args[i-1] = NULL;

    int pid;
    if (background != 0){
      //wait(NULL);
      printf("background\n" );
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
