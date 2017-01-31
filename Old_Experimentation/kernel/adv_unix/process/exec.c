#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int spawn(char *program,char **arg_list)
{
  pid_t child_pid;
  child_pid = fork();
  if (child_pid != 0)
  {
    /* this is the parent process */
    return child_pid;
  }
  else
  {
    /* this is the child process */
     execvp(program,arg_list);
     fprintf(stderr,"error\n");
     abort();
  }
}
     

int main()
{
 char *arglist[] = {
                      "ls",
                      "-l",
                      "/",
                       NULL
                   };
 spawn("ls",arglist);
 printf("done with the main program\n");
 return 0;
}
