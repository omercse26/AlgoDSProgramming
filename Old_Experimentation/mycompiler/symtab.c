#include "global.h"

/************************** START OF SYMBOL TABLE **************************/

struct symlist *symtable[HASHSIZE];

unsigned hash(char *s)
{
  unsigned hashval=0;
  for(hashval=0;*s!='\0';s++)
     hashval=(hashval+31)+(*s);
  return hashval%HASHSIZE;
}
struct symlist *lookup(char *s,int funcno)
{
 struct symlist *np = symtable[hash(s)];
 for(;np!=NULL;np=np->next)
 {
   if (strcmp(s,np->name)==0&&funcno==np->funcno)
     return np;
 }
 return NULL;
}

void install(char *name,int value,int funcno,int offset)
{
 struct symlist *np;
 unsigned hashval;
 if ((np=lookup(name,funcno))==NULL)
 {
   np = (struct symlist*)malloc(sizeof(struct symlist));
   if (np == NULL)
   {
    printf("\n pointer error:no more symbol table\n");
    exit(0);
   }
   hashval = hash(name);
   strcpy(np->name,name);
   np->value = value;
   np->offset = offset;
   np->funcno = funcno;
   np->next = symtable[hashval];
   symtable[hashval] = np;
 }
}
/************************** END OF SYMBOL TABLE **************************/






