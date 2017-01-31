#include<stdio.h>
#include<conio.h>
struct stack
{
 int disk;
 int from;
 int inter;
 int to;
} stack[100];
int top;
void hanoi(int,int,int,int);
void push(int,int,int,int);
struct stack pop();
int main()
{
 clrscr();
 hanoi(3,1,2,3);
 getch();
 return 0;
}



void hanoi(int n,int from,int inter,int to)
{
 /*if (n!=0)
 {
   hanoi(n-1,a,c,b);
   printf("move %d disk from %d to %d\n",n,a,c);
   hanoi(n-1,b,a,c);
 } */
 struct stack parent;
 int temp;
 push(n,from,inter,to);
 while(top>0)
 {
   /* if leaf has come pop print and push */
   /* push immediately after a pop to get binary tree fashion and */
   /* in order traversal */
   if(n<=1)
   {
     parent = pop();
     n = parent.disk;
     inter  = parent.from;
     from   = parent.inter;
     to     = parent.to;
     top--;
     /* for n=1 there wont be any left or right sub trees */
     /* this condition is the termination condition in the recursion */
     if (n>1)
      push(--n,from,inter,to);/* n-1 will also be same */
   }
   else
   {
     temp=to;
     to = inter;
     inter = temp;
     push(--n,from,inter,to);
   }
  }
}

void push(int n,int from,int inter,int to)
{
 stack[++top].disk = n;
 stack[top].from = from;
 stack[top].inter = inter;
 stack[top].to = to;
 printf("top:%d disk:%d from:%d inter:%d to:%d\n", top,stack[top].disk,stack[top].from,stack[top].inter,stack[top].to);
}
struct stack pop()
{
 printf("move %d disk from %d to %d\n",stack[top].disk,stack[top].from,
                                       stack[top].to);
 return stack[top];
}

