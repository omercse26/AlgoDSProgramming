/*notation by niclaus wirth
  P(i,j) = Ak:0<=k<j;S(i+k) = p(k)
  Q(i) = Ak:0<=k<i:~P(k,M)          */
#include<stdio.h>
#include<conio.h>
char input[100];
char pattern[50];
int p(int,int);
void main()
{
  clrscr();
  int li=0;
  int lp=0;
  int i=-1,found = 0;
  printf("enter the string\n");
  scanf("%s",input);
  printf("enter the pattern\n");
  scanf("%s",pattern);
  while(input[++li]!='\0'|| pattern[++lp]!='\0')
  {}
  do
  {
   i=i+1;
   found = p(i,lp);
  }while(found == 1 && i!=li-lp);
  if (found == 0)
    printf("success at \n%d",i+1);
  else
    printf("failure");
  getch();
}

int p(int i,int lp)
{
  for(int j=0;j<lp;j++)
  {
   if(input[i+j] == pattern[j])
   {
    continue;
   }
   else
   {
    return 1;
   }
  }
  return 0;
  /*int j=0;
  while (j<lp && input[i+j] == pattern[j])
    j++;
  */
}