#ifndef lint
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define YYPREFIX "yy"
#line 1 "calc1.y"
 
  #include<stdio.h>
  #include<stdlib.h>
  #include<stdarg.h>
  #include "calc.h" 

TagNode* opr_fn(int oper,int nops,...);
TagNode* id(int i);
TagNode* con(int value);
void freenode(TagNode *p);
int ex(TagNode *p);

void yyerror(char *s);
int sym[26];
#line 17 "calc1.y"
typedef union
{
 int iValue;
 char sIndex;
 TagNode *nPtr;
} YYSTYPE;
#line 39 "y.tab.c"
#define YYERRCODE 256
#define INTEGER 257
#define VARIABLE 258
#define WHILE 259
#define IF 260
#define PRINT 261
#define IFX 262
#define ELSE 263
#define GE 264
#define LE 265
#define EQ 266
#define NE 267
#define UMINUS 268
const short yylhs[] = {                                        -1,
    0,    0,    1,    1,    1,    1,    1,    1,    1,    1,
    3,    3,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,
};
const short yylen[] = {                                         2,
    2,    0,    1,    2,    3,    4,    5,    5,    7,    3,
    1,    2,    1,    1,    2,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,
};
const short yydefred[] = {                                      2,
    0,   13,    0,    0,    0,    0,    0,    3,    0,    0,
    1,    0,    0,    0,    0,   14,    0,   15,    0,   11,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    4,    0,    0,    0,    5,   26,   10,   12,    0,
    0,    0,    0,    0,    0,    0,    0,   18,   19,    6,
    0,    0,    7,    0,    0,    9,
};
const short yydgoto[] = {                                       1,
   11,   12,   21,
};
const short yysindex[] = {                                      0,
   97,    0,  -47,  -21,  -16,  -40,  -40,    0,  -40,   97,
    0,   49,  -40,  -40,  -40,    0,   55,    0,  -39,    0,
   44,  -40,  -40,  -40,  -40,  -40,  -40,  -40,  -40,  -40,
  -40,    0,   76,  -32,  -25,    0,    0,    0,    0,    9,
    9,    9,    9,    9,    9,  -35,  -35,    0,    0,    0,
   97,   97,    0, -238,   97,    0,
};
const short yyrindex[] = {                                      0,
    0,    0,   85,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    4,
    8,   12,   16,   21,   28,  -12,   -1,    0,    0,    0,
    0,    0,    0,    1,    0,    0,
};
const short yygindex[] = {                                      0,
  110,  157,    0,
};
#define YYTABLESIZE 358
const short yytable[] = {                                       9,
    8,   37,   30,   28,    7,   29,   30,   31,   51,   30,
   28,   31,   29,   13,   31,   52,   30,   28,   14,   29,
   27,   31,   26,   15,   55,    0,    0,   27,   16,   26,
   16,    0,   16,    0,   27,    0,   26,    0,    0,   17,
    8,   17,    0,   17,   22,    8,   16,   16,   23,   16,
   30,   28,   24,   29,    0,   31,   25,   17,   17,    8,
   17,   21,   22,   22,    0,   22,   23,   23,   20,   23,
   24,   24,    0,   24,   25,   25,    0,   25,    0,   21,
   21,    0,   21,    9,    0,    0,   20,   20,    7,   20,
   30,   28,    0,   29,    0,   31,   30,   28,    0,   29,
    0,   31,    8,    0,    0,    0,    0,   32,   27,    0,
   26,    0,    0,   36,   27,    0,   26,   30,   28,   20,
   29,    0,   31,    8,    0,    8,   14,   14,    0,   14,
   39,   14,    0,    0,   50,   27,    9,   26,    0,    0,
    0,    7,    0,   14,   14,    0,   14,    0,    0,    0,
    0,    0,    0,    0,    0,    8,    0,    0,    0,    0,
   53,   54,   17,   18,   56,   19,   10,    0,   38,   33,
   34,   35,    0,    0,    0,    0,    0,    0,   40,   41,
   42,   43,   44,   45,   46,   47,   48,   49,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    2,   16,    0,   10,
    0,    0,    0,    0,   22,   23,   24,   25,    0,    0,
    0,   22,   23,   24,   25,    0,    0,    0,   22,   23,
   24,   25,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   16,   16,   16,   16,    0,    0,    8,    8,    8,
    8,    8,   17,   17,   17,   17,    0,   22,   22,   22,
   22,   23,   23,   23,   23,   24,   24,   24,   24,   25,
   25,   25,   25,    0,   21,   21,   21,   21,    0,    0,
    0,   20,   20,   20,   20,    0,    0,    0,    0,    0,
    2,    3,    4,    5,    6,    0,    0,    0,    0,    0,
    0,    0,   22,   23,   24,   25,    0,    0,   22,   23,
   24,   25,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   22,
   23,   24,   25,    0,    0,    0,    0,    0,   14,   14,
   14,   14,    0,    2,    3,    4,    5,    6,
};
const short yycheck[] = {                                      40,
    0,   41,   42,   43,   45,   45,   42,   47,   41,   42,
   43,   47,   45,   61,   47,   41,   42,   43,   40,   45,
   60,   47,   62,   40,  263,   -1,   -1,   60,   41,   62,
   43,   -1,   45,   -1,   60,   -1,   62,   -1,   -1,   41,
   40,   43,   -1,   45,   41,   45,   59,   60,   41,   62,
   42,   43,   41,   45,   -1,   47,   41,   59,   60,   59,
   62,   41,   59,   60,   -1,   62,   59,   60,   41,   62,
   59,   60,   -1,   62,   59,   60,   -1,   62,   -1,   59,
   60,   -1,   62,   40,   -1,   -1,   59,   60,   45,   62,
   42,   43,   -1,   45,   -1,   47,   42,   43,   -1,   45,
   -1,   47,   59,   -1,   -1,   -1,   -1,   59,   60,   -1,
   62,   -1,   -1,   59,   60,   -1,   62,   42,   43,   10,
   45,   -1,   47,  123,   -1,  125,   42,   43,   -1,   45,
   21,   47,   -1,   -1,   59,   60,   40,   62,   -1,   -1,
   -1,   45,   -1,   59,   60,   -1,   62,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   59,   -1,   -1,   -1,   -1,
   51,   52,    6,    7,   55,    9,  123,   -1,  125,   13,
   14,   15,   -1,   -1,   -1,   -1,   -1,   -1,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   31,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,   -1,  123,
   -1,   -1,   -1,   -1,  264,  265,  266,  267,   -1,   -1,
   -1,  264,  265,  266,  267,   -1,   -1,   -1,  264,  265,
  266,  267,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  264,  265,  266,  267,   -1,   -1,  257,  258,  259,
  260,  261,  264,  265,  266,  267,   -1,  264,  265,  266,
  267,  264,  265,  266,  267,  264,  265,  266,  267,  264,
  265,  266,  267,   -1,  264,  265,  266,  267,   -1,   -1,
   -1,  264,  265,  266,  267,   -1,   -1,   -1,   -1,   -1,
  257,  258,  259,  260,  261,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  264,  265,  266,  267,   -1,   -1,  264,  265,
  266,  267,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  264,
  265,  266,  267,   -1,   -1,   -1,   -1,   -1,  264,  265,
  266,  267,   -1,  257,  258,  259,  260,  261,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 268
#if YYDEBUG
const char * const yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,"';'",
"'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,"INTEGER","VARIABLE","WHILE","IF","PRINT","IFX","ELSE","GE","LE",
"EQ","NE","UMINUS",
};
const char * const yyrule[] = {
"$accept : function",
"function : function stmt",
"function :",
"stmt : ';'",
"stmt : expr ';'",
"stmt : PRINT expr ';'",
"stmt : VARIABLE '=' expr ';'",
"stmt : WHILE '(' expr ')' stmt",
"stmt : IF '(' expr ')' stmt",
"stmt : IF '(' expr ')' stmt ELSE stmt",
"stmt : '{' stmt_list '}'",
"stmt_list : stmt",
"stmt_list : stmt_list stmt",
"expr : INTEGER",
"expr : VARIABLE",
"expr : '-' expr",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr GE expr",
"expr : expr LE expr",
"expr : expr EQ expr",
"expr : expr NE expr",
"expr : '(' expr ')'",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 78 "calc1.y"

TagNode* con(int iValue)
{
 TagNode *p;

 if ((p=(TagNode*)malloc(sizeof(Connode)))==NULL)
    yyerror("out of memory");
 
 p->type = CON;
 p->con.value = iValue;
 
 return p;

}

TagNode* id(int sIndex)
{
  
 TagNode *p;

 if ((p=(TagNode*)malloc(sizeof(Idnode)))==NULL)
    yyerror("out of memory");
 
 p->type = ID;
 p->id.i = sIndex;
 
 return p;
  
}

TagNode* opr_fn(int oper1,int nops1,...)
{
  va_list ap;
  TagNode *p;
  size_t size;
  int i;

  size = sizeof(Opnode)+(nops1-1)*sizeof(TagNode*);
  if ((p=(TagNode*)malloc(size))==NULL)
  {
    yyerror("out of memory");
  }

  p->type = OP;
  p->opr.oper = oper1;
  p->opr.nops = nops1;
  va_start(ap,nops1);
  for(i=0;i<nops1;i++)
    p->opr.op[i]=va_arg(ap,TagNode*);
  va_end(ap);
  return p;
}

void freenode(TagNode *p)
{ 
  int i;
  if(!p) return;
  
  if(p->type == OP)
  {
     for(i=0;i<p->opr.nops;i++)
     {
       freenode(p->opr.op[i]);
     }
  }
  free(p);
}

void yyerror(char *s)
{
  fprintf(stdout,"%s\n",s);
}


int ex(TagNode *p)
{
  switch(p->type)
  {
    case CON:
               return p->con.value;

    case ID:
               return sym[p->id.i];

    case OP:

              switch(p->opr.oper)
              {
                 case WHILE:
                              while(ex(p->opr.op[0]))
                                    ex(p->opr.op[1]);

                 
                 case IF:
               		      if (ex(p->opr.op[0]))
                                    ex(p->opr.op[1]);
                              else if( (p->opr.nops) > 2)
                                    ex(p->opr.op[2]); 
                 case ';':

                              ex(p->opr.op[0]);
   			      return ex(p->opr.op[1]);

                 case '=' :
                              return sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);

                 case UMINUS:
               		      return -ex(p->opr.op[0]);

                 case '+':

                              return (ex(p->opr.op[0]) + ex(p->opr.op[1]));

                 case '-':

                              return (ex(p->opr.op[0]) - ex(p->opr.op[1]));

                 case '*':

                              return (ex(p->opr.op[0]) * ex(p->opr.op[1]));

                 case '/':
                              return (ex(p->opr.op[0]) / ex(p->opr.op[1]));

                 case '>':

                              return (ex(p->opr.op[0]) > ex(p->opr.op[1]));

                 case '<':

                              return (ex(p->opr.op[0]) < ex(p->opr.op[1]));

                 case GE:

                              return (ex(p->opr.op[0]) >= ex(p->opr.op[1]));
                 case LE:

                              return (ex(p->opr.op[0]) <= ex(p->opr.op[1]));
                                
                 case EQ:

                              return (ex(p->opr.op[0]) ==  ex(p->opr.op[1]));
                                

                 case NE:

                              return (ex(p->opr.op[0]) != ex(p->opr.op[1]));

                 case PRINT:
                              printf("%s\n",ex(p->opr.op[0]));
                 }        
  }

}
                                	                          
int main(void)
{
 yyparse();
 return 0;
}   


  
 
    


#line 412 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 38 "calc1.y"
{ ex(yyvsp[0].nPtr);freenode(yyvsp[0].nPtr);}
break;
case 3:
#line 43 "calc1.y"
{yyval.nPtr = opr_fn(';',2,NULL,NULL);}
break;
case 4:
#line 44 "calc1.y"
{yyval.nPtr = yyvsp[-1].nPtr;}
break;
case 5:
#line 45 "calc1.y"
{yyval.nPtr = opr_fn(PRINT,1,yyvsp[-1].nPtr);}
break;
case 6:
#line 46 "calc1.y"
{yyval.nPtr = opr_fn('=',2,yyvsp[-3].sIndex,yyvsp[-1].nPtr);}
break;
case 7:
#line 47 "calc1.y"
{yyval.nPtr = opr_fn(WHILE,2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 8:
#line 48 "calc1.y"
{yyval.nPtr = opr_fn(IF,2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 9:
#line 49 "calc1.y"
{yyval.nPtr = opr_fn(IF,3,yyvsp[-4].nPtr,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 10:
#line 50 "calc1.y"
{yyval.nPtr = yyvsp[-1].nPtr;}
break;
case 11:
#line 55 "calc1.y"
{yyval.nPtr = yyvsp[0].nPtr;}
break;
case 12:
#line 56 "calc1.y"
{yyval.nPtr = opr_fn(';',2,yyvsp[-1].nPtr,yyvsp[0].nPtr);}
break;
case 13:
#line 61 "calc1.y"
{yyval.nPtr = con(yyvsp[0].iValue);}
break;
case 14:
#line 62 "calc1.y"
{yyval.nPtr = id(yyvsp[0].sIndex); }
break;
case 15:
#line 63 "calc1.y"
{yyval.nPtr = opr_fn(UMINUS,1,yyvsp[0].nPtr);}
break;
case 16:
#line 64 "calc1.y"
{yyval.nPtr = opr_fn('+',2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 17:
#line 65 "calc1.y"
{yyval.nPtr = opr_fn('+',2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 18:
#line 66 "calc1.y"
{yyval.nPtr = opr_fn('+',2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 19:
#line 67 "calc1.y"
{yyval.nPtr = opr_fn('+',2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 20:
#line 68 "calc1.y"
{yyval.nPtr = opr_fn('+',2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 21:
#line 69 "calc1.y"
{yyval.nPtr = opr_fn('+',2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 22:
#line 70 "calc1.y"
{yyval.nPtr = opr_fn('+',2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 23:
#line 71 "calc1.y"
{yyval.nPtr = opr_fn('+',2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 24:
#line 72 "calc1.y"
{yyval.nPtr = opr_fn('+',2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 25:
#line 73 "calc1.y"
{yyval.nPtr = opr_fn('+',2,yyvsp[-2].nPtr,yyvsp[0].nPtr);}
break;
case 26:
#line 74 "calc1.y"
{yyval.nPtr = yyvsp[-1].nPtr;}
break;
#line 707 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
