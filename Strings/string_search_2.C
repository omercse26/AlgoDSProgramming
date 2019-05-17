/*notation by niclaus wirth
  P(i,j) = Ak:0<=k<j;S(i+k) = p(k)
  Q(i) = Ak:0<=k<i:~P(k,M)          */
#include<stdio.h>
#include<conio.h>
char input[100];
char pattern[50];
void main()
{

  int li=0;
  int lp=0;
  int i=-1,j = 0;
  clrscr();
  printf("enter the string\n");
  scanf("%s",input);
  printf("enter the pattern\n");
  scanf("%s",pattern);
  while(input[++li]!='\0'|| pattern[++lp]!='\0')
  {}
  do
  {
   i=i+1;
   while (j<lp && input[i+j] == pattern[j])
    j++;
  }while(j!=lp && i!=li-lp);
  if (j==lp)
    printf("success at \n%d",i+1);
  else
    printf("failure");
  getch();
}

