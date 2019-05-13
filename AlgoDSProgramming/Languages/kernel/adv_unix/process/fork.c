#include<stdio.h>
#include<sys/types.h>
//#include<unistd.h>
int main()
{
 pid_t child_pid;
 printf("the main program process id is %d\n",(int)getpid());
 child_pid = fork();
 if (child_pid!=0)
 {
    printf("if :this is parent process with id %d\n",(int)getpid());
    printf("if :the child process id is %d\n",child_pid);
 }
 else
 {
    printf("else :this is the child process id : %d\n",(int)getpid()); 
 }
 return 0;
}
