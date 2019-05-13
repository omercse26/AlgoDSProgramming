/********************  CODE GENERATOR *************************************/
void codegenerator()
{
 char a[10],*line[5],**temp;
 while(1)
 {
   temp = (char*) get_line();
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

void** get_line()
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
}
