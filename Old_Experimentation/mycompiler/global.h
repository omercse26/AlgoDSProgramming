#include<stdio.h>
#ifndef _GLOBAL_H
#define _GLOBAL_H 1
#define COMPHOME "/home/mycompiler"

#define HASHSIZE 10
#define MAXFUNCTION 100

FILE *fp;
FILE *fin;

char token[80];
char token_type;
char key;
int t=0,offset;
int func_underscan=-1;


enum tok_types { DELIM,IDENT,NUM,KEY,BLOCK,FUNCNAME};
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

struct funclist
{
  char funcname[20];
  int funcno;
  int  return_type;
}functable[MAXFUNCTION];

struct temp
{
  char t[4];
  int n;
}temp_table[100];

struct symlist
{
 struct symlist *next;
 char name[4];
 int value;
 int offset;
 int funcno;
 struct addr_desc
 {
   char addr[10];
   char type;
   struct addr_desc *next;
 }addr_desc;
};
extern struct symlist *symtable[HASHSIZE];

/* compiler interfaces */

extern int gettoken(void);
extern void parser(void);
extern void codegenerator();
extern void** get_line (void);
extern void emit(char *);
void emitline(char *);
#endif
