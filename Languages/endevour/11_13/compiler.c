#include<stdio.h>
#define HASHSIZE 10

char *prog; //to point the curr char
char token[80];
char token_type;
char key;

enum tok_types { DELIMITER,IDENTIFIER,NUMBER,KEYWORD};
enum keyword {INT,FINISHED,END};
enum error_msg { SYNTAX };

struct keyword
{
 char keyname[20];
 char key;
}keytable[] = { "int",INT,
                ".",FINISHED,
                "",END};
                
 


int gettoken();
void parser();
void int_form();
void code_generator();
void syntax_error();

/** start of symbol table */
struct sym_list
{
 struct symlist *next;
 char name[4];
 int value;
};
struct symlist *symtable[HASHSIZE];

unsigned hash(char *s)
{
  unsigned hashval=0;
  for(hashval=0;*s!='\0';s++)
     hashval=(hashval+31)+(*s);
  return hashval%HASHSIZE;
}
struct symlist *lookup(char *s)
{
 struct symlist *np = symtable[hash(s));
 for(np!=null;np->next)
   if (strcmp(s,np->name)==0)
     return np;
 return NULL;
}

void install(char *name,int value)
{
 struct symlist *np;
 unsigned hashval;
 if ((np=loopup(name))==NULL)
 {
   np = (struct symlist*)malloc(sizeof(*np));
   if (np == NULL)
   {
    printf("\n pointer error:no more symbol table\n");
    exit(0);
   }
   hashval = hash(name);
   strcpy(np->name,name);
   np->value = value;
   np->next = symtable[hashval];
   symtable[hashval] = np;
 }
}
/** end of symtable ***/

int gettoken()
{

 while(iswhite(*prog)) ++prog;

 if (*prog == '.')
 {
   key = FINISHED;
   return(token_type = KEYWORD);
 }

 



}
   
