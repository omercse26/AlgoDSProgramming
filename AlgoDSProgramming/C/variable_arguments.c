#include<stdarg.h>
#include<stdio.h>
void minprint(char*,...);
int main()
{
  char *a="omer asif\n";
  minprint("%s",a);
  return 0;
}

void minprint(char *fmt,...)
{
 va_list ap;
 char *p,*sval;
 int ival;
 double dval;
 va_start(ap,fmt);
 for(p=fmt;*p;p++)
 {
   if(*p!='%')
   {
     putchar(*p);
     continue;
   }
   switch(*++p)
   {
     case 'd':
              ival = va_arg(ap,int);
              printf("%d",ival);
              break;
     case 'f':
  	      dval = va_arg(ap,double);
              printf("%f",dval);
              break;
     case 's':
              sval = va_arg(ap,char*);
              printf("%s",sval);
              break;
     default:
              putchar(*p);
              break;
   }
 }
 va_end(ap);
}     
