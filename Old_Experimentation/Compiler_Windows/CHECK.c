#include<stdio.h>
#include<conio.h>
#define HASHSIZE 10
#define MAXFUNCTION 100

FILE *fp;
FILE *fin;

void error(char*);
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


int gettoken(void);
void parser(void);
char* rvalue(void);
char* term(void);
char* newtemp(void);
char* lvalue(void);
struct list* expr_list(void);
/*void int_form();*/
void codegenerator();
char* getreg(void);
void** getline(void);
/*void syntax_error();
*/
/************************** START OF SYMBOL TABLE **************************/
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

int gettoken()
{
 char temp[10];int i=0;
 char prog;
 while(isspace(prog=fgetc(fin))) {}
 //printf("%c\n",prog);

 if (prog == EOF)
 {
   key = FINISHED;
   return(token_type = EOF);
 }

 if (strchr("{}",prog))
 {
   temp[i++]=prog;
   temp[i]='\0';
   strcpy(token,temp);
   return (token_type == BLOCK);
 }


 if (strchr("+-*/=;(),",prog))
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
     temp[i++]=prog;prog=fgetc(fin);
   }
   else
   {
    error("digit");
   }
  } // if isdigit
  temp[i]= '\0';
  strcpy(token,temp);
  ungetc(prog,fin);
  return (token_type = NUM);
 }

 if (isalpha(prog))
 {
  while(isalnum(prog))
  {
   temp[i++]=prog;prog=fgetc(fin);
  }
  temp[i] = '\0';
  strcpy(token,temp);
  //if (!strcmp(temp,"printa")) printf("aa  %s\n",temp);
  ungetc(prog,fin);
  i=0;
  while(keytable[i].key!=END)
  {
   if(strcmp(keytable[i].keyname,token)==0)
   {
    key = keytable[i].key;
    return (token_type = KEY);
   }
   i++;
  }
  for(i=0;i<MAXFUNCTION;i++)
  {
    //printf("aa\n");
    if(!strcmp(token,functable[i].funcname))
    {
      return (token_type = FUNCNAME);
    }
  }
  return (token_type = IDENT);
 }//if isalpha
}
/********************end oflexer**********************************************/
/************************** START OF PRESCAN ********************************/
void prescan()
{
  int brace = 0,func_index = 0,datatype,functno=0;
  char temp[20];
  do
  {
    while(brace)
    {
      gettoken();
      if(!strcmp(token,"{")) brace++;
      if(!strcmp(token,"}")) brace--;
    }
    gettoken();
    //printf("start %s\n",token);
    if(token_type == KEY && key == INT)
    {
      datatype = key;
      gettoken();
      if(token_type == IDENT)
      {
        printf("ident %s\n",token);
        strcpy(temp,token);
        gettoken();
        if(!strcmp(token,"("))
        {
          strcpy(functable[func_index].funcname,temp);
          functable[func_index].return_type = datatype;
          functable[func_index].funcno = functno;
          functno++;
          func_index++;
          while(strcmp(token,")")) gettoken();
        }
        else
           error("expected (");
      }//IF IDENT
      else if (token_type == KEY)
         error("expected ident yet keyword");
    }//IF KEY
    else if(token_type != EOF)
    {
      error("expected KEY II");
    }// end of if key
    gettoken();
    //printf("toekn %d \n",token_type);
    if (!strcmp(token,"{")) brace++;
    else if(token_type != EOF) error("expected {");
  }while(token_type != EOF);
}

/*************************** END OF PRESCAN********************************/



void error(char *s)
{
 printf("%s ",s);
 printf("but %s\n",token);
 exit(0);
}



/*************************************  MAIN  ******************************/

int main()
{
 int a,i;
 clrscr();
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

void init()
{
  int i;
  fp = fopen("D:\\DJGPP\\bin\\src\\c\\output.txt","w");
  fin = fopen("D:\\DJGPP\\bin\\src\\c\\input.c","r");
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
  fp = fopen("D:\\DJGPP\\bin\\src\\c\\output1.asm","w");
  fin = fopen("D:\\DJGPP\\bin\\src\\c\\output.txt","r");
  if (fin == NULL)
    printf("file not found\n");
  //gettoken();
}

/*************************************************************/
/**  parse routine starts here **/

void parse()
{
  //printf("TODO\n");
  offset = 0;
  func_definition();
  while(1)
  {
    if(token_type == EOF)
      break;
    else
    {
      offset = 0;
      func_definition();
    }
  }
  //decl();
  //body();

}

void func_definition()
{
   type_specifier();
   func_identifier();
   match("(");
   printf("ok\n");
   getch();
   if(token_type == KEY && key == INT)
   {
     while(1)
     {
       type_specifier();
       param();
       if(strcmp(token,","))
       {
         match(")");
         break;
       }
       else
       {
          match(",");
       }
     } //while(1)
  }
  else if(!strcmp(")" ,token))
    match(")");
  else
    error("funct def");
  block();
}

void type_specifier()
{
 if(token_type == KEY && key == INT)
 {
   gettoken();
 }
 else
 {
   error("type");
 }
}

void func_identifier()
{
 int i;
 for(i=0;i<MAXFUNCTION;i++)
   if(!strcmp(token,functable[i].funcname))
   {
     func_underscan = functable[i].funcno;
     emit("_");emit(token);emitline(":");
     gettoken();break;
   }
 if (i==MAXFUNCTION)
 error("func not defined");
}

void param()
{
 if(token_type == IDENT)
   gettoken();
 else
   error("param");
}

void block()
{
 //getch();
 match("{");
 while(1)
 {
  //printf("block %s\n",token);
  //getch();
  if(token_type == KEY && key==INT)
    decl();
  else
    break;
  //printf("block %s\n",token);
 }
 while(1)
 {
   //printf("block %s %d\n",token,token_type);
   if (token_type == IDENT || token_type == KEY || token_type == BLOCK
       || token_type == FUNCNAME)
      statement();
   else
      break;
 }
 //printf("block %d\n",token_type);
 match("}");
}

void decl()
{
 datatype();
 ident();
 printf("after");
 match(";");
 while(1)
 {
   //printf("decl :%s\n",token);
   if(token_type==KEY && key == INT)
   {
     datatype();
     ident();
     match(";");
   }
   else
   {
     break;
   }
 }
}

void statement()
{
 struct list
 {
    char temp[10];
    struct list *next;
 } *queue=NULL;
 char func[10];
 if(token_type == IDENT)
   expr();
 else if(token_type == FUNCNAME)
 {
  strcpy(func,token);
  gettoken();match("(");
  queue = expr_list();
  //printf("addr :%s\n",queue->temp);
  for(;queue!=NULL;queue=queue->next){
    emit("param ");emitline(queue->temp); }
  match(")");match(";");
  emit("call _");emitline(func);
 }
}

struct list *expr_list()
{
 struct list
 {
  char temp[10];
  struct list *next;
 } *queue=NULL,*front=NULL,*local=NULL;

 while(1)
 {
   if(!strcmp(token,")")) break;
   else
   {
     printf("start token in %s\n",token);
     local = (struct list*) malloc (sizeof(struct list));
     //local->temp = (char*) malloc (sizeof(10));
     strcpy(local->temp,rvalue());
     printf("listi :%s %s\n",local->temp,token);
     local->next=NULL;
     if (queue == NULL)
     {
       queue=local;
     }
     else
     {
       queue->next=local; queue = queue->next;
     }
     if(front == NULL)
       front = queue;
     if(!strcmp(token,","))
     {
       //printf("token in %s\n",token);
       match(",");
       //printf("token after %s\n",token);
     }

   }
 }
 //printf("raddr :%s\n",front->temp);
 for(queue=front;queue!=NULL;queue=queue->next){
    printf("raddr :%s\n",queue->temp); }
 return front;
}

void expr()
{
 char place[10],result[10];
 strcpy(place,lvalue());
 match("=");
 //printf("expr : %s\n",token);
 strcpy(result,rvalue());
 match(";");
 printf("result %s\n",result);
 emit(place);emit("=");emitline(result);
 while(1)
 {
   if(token_type == IDENT)
   {
    strcpy(place,lvalue());
    //strcpy(place,token);
    match("=");
    //printf("expr : %s\n",token);
    strcpy(result,rvalue());
    match(";");
    emit(place);emit("=");emitline(result);
   }
   else
   {
     break;
   }
 }
}

char* rvalue()
{
 char newt[10],value1[10],value2[10],*a;
 a = (char*)malloc(sizeof(10));
 //value1 = term();
 strcpy(value1,term());
 //printf("rvalue :%s\n",value1);
 while(1)
 {
  //printf("rvalue in:\"%s\"\n ",token);
  //;getch();exit(0);
  if(!strcmp(token,"+"))
  {
       match("+");
       strcpy(newt,newtemp());
       //printf("rvalue in brf:\"%s\"\n ",token);
       strcpy(value2,term());
       //printf("rvalue in aftr:\"%s\"\n ",token);
       emit(newt);emit("=");emit(value1);emit("+");
       emitline(value2);
       strcpy(value1,newt);
   }
   else
   {
      strcpy(a,value1);
      return a;
   }
 }
}

char* term()
{
 struct symlist *ide; char *a;
 a = (char*)malloc(sizeof(10));
 if(token_type == IDENT)
 {
   if((ide=lookup(token,func_underscan)) == NULL)
     error("not defined");
   else
   {
     gettoken();
     return ide->name;
   }
 }
 else if(token_type ==NUM)
 {
  strcpy(a,token);
  gettoken();
  //printf("term NUM %s %s\n",a,token);
  return a;
 }
 else
 {
   error("term");
 }
 return "error";
}

char* lvalue()
{
 struct symlist *var;
 char *a;
 a = (char*)malloc(sizeof(10));
 if (token_type == IDENT)
 {
   if ((var=lookup(token,func_underscan)) == NULL)
   {
    error("undefined variable");
   }
   else
   {
    strcpy(a,token);
    gettoken();
    return a;
   }
 }
 else
 {
   error("lvalue");
 }
}

void match(char* s)
{
 if(!strcmp(s,token))
 {
   gettoken();
   //printf("match %s %d\n",token,token_type);
 }
 else
 {
   printf("expected :%s but %s\n",s,token);
   error("syntax error");
 }
}

void datatype()
{
 if (token_type == KEY && key == INT)
 {
       gettoken();
       printf("datat %s\n",token);
 }
}

void ident()
{
 int value;char *a;a=(char*) malloc (sizeof(10));
 //printf("identii :%s\n",token);
 if(token_type== IDENT)
 {
         install(token,value,func_underscan,offset);
         emit("push ");emit(token);emit("  ");emitline(itoa(offset,a,10));
         offset = offset+4;
         gettoken();
 }
 //printf("identii :%s\n",token);

}

/***************************** END OF PARSER **********************************************/
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
/********************  CODE GENERATOR *************************************/
void codegenerator()
{
 char a[10],*line[5],**temp;
 while(1)
 {
   temp = (char*) getline();
   line[0] = *temp;
   line[1] = *(temp+1);
   line[2] = *(temp+2);
   line[3] = *(temp+3);
   line[4] = *(temp+4);
   //printf("code :%c\n",**(line+4));
   if(line[0] == NULL)
     break;
   else if(!strcmp(line[0],"_main:"))
   {
       //printf("codesss :%s\n",line[0]);
       emitline("push ebp");
       emitline("subl esp,4");
       emitline(line[0]);
   }
   else if(!strcmp(line[1],"push"))
   {
      strcpy(a,getreg());
      emitline("subl esp,4");
   }
   else if(!strcmp(line[1],"param"))
   {
       emit("mov eax,");emitline(line[2]);
       emitline("push eax");
       strcpy(a,getreg());
   }
   else if(!strcmp(line[1],"call"))
   {
        emit("call ");emitline(line[2]);
   //break;
   }
   else if(**(line)=='_')
   {
     emitline(line[0]);
     emitline("push ebp");
     emitline("subl esp,4");
   }
   else
   {
      emit("mov eax,");emitline(line[2]);
      emit("mov ebx,");emitline(line[3]);
      emit("add ");emitline("ebx");
   }
  }
}


char* getreg()
{
 //char *reg[]={"eax","ebx","ecx","edx","egx","efx"};
 return "eax";
}

void** getline()
{
  char *start,*line,*op1_start,*op2_start,*op3_start,*op1,*op2,*op3,*oper,*oper_start,c,*pack[5];
  int count=1,line_count = 1;
  start    =line= (char*)malloc(sizeof(100));
  op1_start=op1 = (char*)malloc(sizeof(100));
  op2_start=op2 = (char*)malloc(sizeof(100));
  op3_start=op3 = (char*)malloc(sizeof(100));
  oper_start=oper= (char*)malloc(sizeof(100));
  while((c=fgetc(fin))!=EOF && c !='\n')
  {
    *line=c;
    line++;
    if (isalnum(c))
      switch(count){
      case 1:
           *op1 = c;
           op1++;
           break;
      case 2:
           *op2 = c;
           op2++;
           break;
      case 3:
           *op3 = c;
           op3++;
           break;   }
     else
     {
          *oper = c;
          //oper++;
          count++;
     }
     //printf("line : %c %c ||",*(line-1),c);
     line
  }
  oper++;
  *line = *op1= *op2= *op3= *oper = '\0';
  pack[0]=start;pack[1]=op1_start;pack[2]=op2_start;pack[3]=op3_start;
  pack[4]=oper_start;
  if (c=='\n')
  {
    //fgetc(fin);
    //printf("omer :%s\n",pack[2]);
    return pack;
  }
  else if(c==EOF)
  {
    pack[0] = pack[1] = pack[2] = pack[3] = NULL;
    printf("EOF :%c",c);
    return &pack;
  }
  else
  {
   return "omer";
  }
}
