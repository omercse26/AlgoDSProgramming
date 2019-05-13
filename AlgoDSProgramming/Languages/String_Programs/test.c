#include<stdio.h>
#include<conio.h>
char* printa(void);
int main()
{
 clrscr();
 char a[10],b[10];int c;
 strcpy(a,printa());
 //a = (char*)malloc(sizeof(10));
 //a[0]='o';
 //printf("%s\n",printa());
 //strcpy(b,a);
 //a[1] = '\0';
 c++=1;
 itoa(1,b,10);
 printf("b %s\n",b);
 strcat(a,b);
 printf("%s\n",a);
 getch();
}
char* printa()
{
 char *a;
 a = (char*)malloc(sizeof(10));
 //char a[10];
 strcpy(a,"omer");
 //printf("in %u %s\n",a,a);
 return a;
}
