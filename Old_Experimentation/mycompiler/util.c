#include "global.h"
#include "string.h"

void error(char *s)
{
 printf("%s ",s);
 printf("but %s\n",token);
 exit(0);
}

/*************************  supporting functions  ************************/
void emit(char *s)
{
 //printf("%s",s);
 fprintf(fp,"%s",s);
}

void emitline(char *s)
{
 emit(s);//printf("\n");
 fprintf(fp,"\n");
}
char* newtemp()
{
 char *a,*b;
 a = (char*)malloc(sizeof(10));
 b = (char*)malloc(sizeof(10));
 strcpy(a,"t");
 //printf("a %s\n",a);
 itoa(t,b,10);
 //printf("t %s b:%s\n",itoa(t),b);
 strcat(a,b);
 //printf("after %s \n",a);
 t++;
 return a;
}
/**************************************************************************/
