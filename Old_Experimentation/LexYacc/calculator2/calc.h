typedef enum{CON,ID,OP} Node;

typedef struct 
{
  Node type;
  int value;
}Connode;

typedef struct
{
 Node type;
 int i;
}Idnode;

typedef struct
{
 Node type;
 int oper;
 int nops;
 union Tag *op[1];
}Opnode;

typedef union Tag
{
 Node type;
 Connode con;
 Idnode id;
 Opnode opr;
}TagNode;

extern int sym[26]; 


