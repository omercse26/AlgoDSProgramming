#include "global.h"

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
void** get_line(void);
/*void syntax_error();*/


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
