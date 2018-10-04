#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
pid_t pid;
int main () {
printf("hello ");
pid=fork();
if ( pid==0 ) {
 printf(" hello world\n");
 exit (0);
 }
 printf("world\n");
}
