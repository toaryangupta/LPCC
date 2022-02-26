%{
    #include<stdio.h>
    int flag=0;
   
   int yylex();
  void yyerror(const char *s);

   
%}
%token NUMBER
// setting the precedence
// and associativity of operators
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%%
ArithmeticExpression: E{
         printf("\nResult=%d\n",$$);
         return 0;
        }
E:E'+'E {$$=$1+$3;}
 |E'-'E {$$=$1-$3;}
 |E'*'E {$$=$1*$3;}
 |E'/'E {$$=$1/$3;}
 |E'%'E {$$=$1%$3;}
 |'('E')' {$$=$2;}
 | NUMBER {$$=$1;}
;
%%

int main()
{
   printf("\n Enter Any Arithmetic Expression :\n");
   yyparse();
  if(flag==0)
  {
      printf("\n -> Entered arithmetic expression is Valid\n\n");
  }
   
  return 0;
}

void yyerror(const char *s)
{
   printf("\n -> Entered arithmetic expression is Invalid\n\n");
   flag=1;
}
