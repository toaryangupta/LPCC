<h2>
  
  [ To evaluate an arithmetic expression using YACC tool ](/Assignment%2004/4a)
  
</h2>


<div class="img">
  <li>Running the files </li>
  <img src="https://user-images.githubusercontent.com/99306046/155846106-52e329b0-360d-40c6-88c5-bfbc4acad865.png"  "/>


</div>

<h3> Lex File- 4a.l</h3>

```lex
                                                                                                                     
%{
#include<stdio.h>
#include "y.tab.h"
extern int yylval;
%}

%%
[0-9]+ {
          yylval=atoi(yytext);
          return NUMBER;
       }
[\t] ;
[\n] return 0;
. return yytext[0];
%%
int yywrap()
{
return 1;
}
```

<h3> Yacc File- 4a.y</h3>

```yacc
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

  ```





