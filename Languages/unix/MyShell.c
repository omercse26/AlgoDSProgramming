#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <sys/wait.h>
#define pid_t int
struct job
{
   pid_t pid;
   int jid;
   char isstopped;
} jobs [100];

int njobs = -1;

char* trim (char* c)
{
   char *e;  
   while (isspace(*c)) ++c;
   if ( *c == '\0') return c;
   e = c + strlen(c) - 1;
   while (isspace(*e)) --e;
   *(e+1) = '\0';
   return c;
}

void addjob(pid_t pid, char stopped)
{
  jobs[++njobs].pid = pid;
  jobs[njobs].jid = njobs;
  jobs[njobs].isstopped = stopped;
  printf ("adding job:%d pid:%d\n", jobs[njobs].jid, jobs[njobs].pid);
}  

void modifyjob (int jid, char stopped)
{
   jobs[jid].isstopped = stopped;
}
void removejob(int jid)
{
  jobs[jid].pid = -1;
  jobs[jid].jid = -1;
}

int findpid (int jid)
{
   if (jid <= njobs)
     return jobs[jid].pid;
   return -1;
}


void printjobs()
{
  int i;
  for (i=0; i<=njobs; i++)
  {
     if (jobs[i].pid != -1)
     {
        printf ("jobid:%d  pid:%d stopped:%d\n", jobs[i].jid, jobs[i].pid, jobs[i].isstopped);
     }
  }

}

void waitforprocess(pid_t pid)
{
  int status; pid_t tid;
  tid = waitpid (pid, &status, WUNTRACED);
  
  if (WIFEXITED(status))  
    printf ("Process %d exited with status:%d\n", pid, WEXITSTATUS(status));  
  else if (WIFSTOPPED(status))
  {
     addjob(pid, 1);
  }
  else if(WIFSIGNALED(status))
  {
    printf ("Process %d terminated by signal:%d\n", pid, WTERMSIG(status));
  }
 }
    
void checkjobstatus()
{
  int i, status, sig;
  pid_t  p;
  for (i=0; i<=njobs; ++i)
  {
     status = 0;
     if (jobs[i].pid != -1)
     {
        p = waitpid(jobs[i].pid, &status, WNOHANG|WUNTRACED|WCONTINUED);
        if (p == jobs[i].pid)
        {
         if (WIFEXITED(status))
         {
           printf ("Job %d exited with status:%d\n", jobs[i].jid,WEXITSTATUS(status));
           removejob (jobs[i].jid);
         }
         else if (WIFSTOPPED(status))
         {
           modifyjob (jobs[i].jid, 1);
         }
         else if (WIFSIGNALED(status))
         {
           sig = WTERMSIG (status);
           if (sig == SIGKILL || sig == SIGTERM || sig == SIGQUIT || sig == SIGINT) {
            printf ("Job %d terminated by signal %d\n", jobs[i].jid, sig);
            removejob (jobs[i].jid);
          }
         }
         else if (WIFCONTINUED(status))
         {
           modifyjob (jobs[i].jid, 0);
         } 
       }
     }
  }
}

void getfilename(char *command, char** argv)
{
  char* delim = " \t\n";
  int i = 0, dist;
  char *ind;
  char *tok = strtok(command, delim);
  argv[i++] = tok;
  while (1)
  {
    tok = strtok(NULL, delim);
    if (tok == NULL) break;
    argv[i++] = tok;
  }
  ind = strchr (argv[i-1], '&');
  if (ind != NULL)
  {
    dist = ind - argv[i-1];
    argv[i-1] = strndup ( argv[i-1], dist);
  }
  if (argv[i-1][0] == '\0')
    argv[i-1] = NULL;
  else
    argv[i] = NULL;
}

void executecommand(char *c)
{
  char* delim = " \t\n";
  char *command, *jid;
  char* bg = 0;
  char** argv = NULL; 
  char* env[] = {NULL};
  int fg = 0;
  pid_t childpid, tid;
  char *duplicate = strdup (c);
  
  if (strcmp ("jobs", c) == 0)
  {
    printjobs(); return;
  }
  command = strtok (c, delim);
  
  if ( (strcmp (command, "fg") == 0 && (fg = 1))||
       (strcmp (command, "bg") == 0 && (fg = 2)) ||
       strcmp (command, "kill") == 0
     )
  {
     jid = strtok (NULL, delim);
     tid = findpid (atoi(jid));
     if (tid == -1)
     {
       printf ("Job %s invalid\n", jid);
       return;
     } 
     switch (fg)
     {
        case 0:
          kill (tid, SIGINT);
          break;
        case 1:
          removejob(atoi(jid));
          kill (tid, SIGCONT);
          waitforprocess(tid);
          break;
        case 2:
          modifyjob(atoi(jid), 0);
          kill(tid, SIGCONT);
          break;
        default:
          printf ("Invalid Job command\n");
          break;
      }
  }
  else
  {
     bg = strchr(duplicate, '&');
     childpid = fork();
     if (childpid == 0)
     {
       argv = (char**) malloc (20*sizeof(char*));
       getfilename(duplicate, argv);
       execve (argv[0], argv, env);
       printf ("Error executing the command %s\n", duplicate);
       exit(-1);
     }
     else
     {
       if (bg == NULL) {
         waitforprocess (childpid);         
       }
       else {
        addjob(childpid, 0);
       }
     }
  
  }
  
}  
int main()
{
  char buf[256], *p;
  while (1)
  {
     printf ("$:");
     fgets (buf, 255, stdin);
     p = trim (buf);
     if (strlen(p) > 0)
        executecommand(p);
     checkjobstatus();
   }
   return 0;
}   
