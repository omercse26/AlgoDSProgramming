#include<stdio.h>
#include<conio.h>
#define HASHSIZE 10
void error(char*);
//char *prog; //to point the curr char
char token[80];
char token_type;
char key;

enum tok_types { DELIM,IDENT,NUM,KEY};
enum keywords {INT,PRINT,FINISHED,END};
enum error_msg { SYNTAX };

struct keyword
{
 char keyname[20];
 char key;
}keytable[] = { "int",INT,
                "print",PRINT,
                ".",FINISHED,                
                "",END};
                
 


int gettoken(void);
void parser(void);
/*void int_form();
void code_generator();
void syntax_error();
*/
/** start of symbol table */
/*struct sym_list
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
}*/
/** end of symtable ***/

int gettoken()
{
 char temp[10];int i=0;
 char prog;
 while(isspace(prog=getche())) {}

 if (prog == '.')
 {
   key = FINISHED;
   return(token_type = '.');
 }

 if (strchr("+-*/=;",prog))
 {
  temp[i++]=prog;
  temp[i]='\0';
  strcpy(token,temp);
  return (token_type = DELIM);
 }
 if (isdigit(prog))
 {
  while(isalnum(prog))
  {
   if (isdigit(prog))
   {
     temp[i++]=prog;prog=getche();
   }
   else
   {
    error("digit");
   }
  }
  temp[i]= '\0';
  strcpy(token,temp);
  ungetch(prog);
  return (token_type = NUM);
 }

 if (isalpha(prog))
 {
  while(isalnum(prog))
  {
   temp[i++]=prog;prog=getche();
  }
  temp[i] = '\0';
  strcpy(token,temp);
  ungetch(prog);
  i=0;
  while(keytable[i].key!=END)
  {
   if(strcmp(keytable[i].keyname,token)==0)
   {
    return (token_type = KEY);
   }
   i++;
  }
  return (token_type = IDENT);
 }
}
   
void error(char *s)
{
 printf("%s\n",s);
}


int main()
{
 int a;
 clrscr();
 /*while((a=gettoken())!='.')
 {
  printf("%s ",token);
  printf("%d\n ",token_type);
 }*/
 parse();
 getch();
}


void parse()
{

