#ifndef YYERRCODE
#define YYERRCODE 256
#endif

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
typedef union
{
 int iValue;
 char sIndex;
 TagNode *nPtr;
} YYSTYPE;
extern YYSTYPE yylval;
