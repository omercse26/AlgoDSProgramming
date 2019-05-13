#include "global.h"

void init()
{
  int i;

  fp = fopen(COMPHOME"output.txt","w");
  fin = fopen(COMPHOME"input.c","r");
  if (fin == NULL)
    printf("file not found\n");
  for(i=0;i<HASHSIZE;i++)
    symtable[i] = NULL;
  //gettoken();
}

void close()
{
  fclose(fp);
  fclose(fin);
}
void secondinit()
{
  int i;
  fp = fopen(COMPHOME"output1.asm","w");
  fin = fopen(COMPHOME"output.txt","r");
  if (fin == NULL)
    printf("file not found\n");
  //gettoken();
}

/*************************************  MAIN  ******************************/

int main()
{
 int a,i;
 
 init();
 /*while((a=gettoken())!=EOF)
 {
  printf("%s ",token);
  printf("%d\n ",token_type);
 }*/
 prescan();
 close();

 init();
 gettoken();
 for(i=0;i<100;i++)
    if(strcmp(functable[i].funcname,""))
      printf("%s %d\n",functable[i].funcname,functable[i].funcno);
 getch();

 parse();
 close();

 secondinit();
 codegenerator();

 close();
 getch();
 //exit(0);
}


