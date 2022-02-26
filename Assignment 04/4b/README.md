<h2>
  
  [ To evaluate or check built-in functions using YACC tool ](/Assignment%2004/4b)
  
</h2>


<div class="img">
  <li>Running the files </li>
  <img src="https://user-images.githubusercontent.com/99306046/155846327-21b13b1d-435d-4d3f-8fd1-c2e7879d5fd2.png"  />



</div>

<h3> Lex File- 4b.l</h3>

```lex
                                                                                                                     
%{

 #include "y.tab.h"

%}

%%
sqrt { return SQRT;}
pow {return POW;}
floor {return FLOOR;}
abs {return ABS;}
[0-9]+ {yylval=atoi(yytext); return NUMBER;}

[a-zA-Z]+ { return string; }
[ \t]+ ; 
\n { return 0; }
. { return yytext[0];}

%%


int yywrap()
{
	return 1;
}               
                  
```

<h3> Yacc File- 4b.y</h3>

```yacc
%{
#include<string.h>
#include <stdio.h>
#include<math.h>
#include<stdlib.h>
void yyerror(char*);
int yylex();

%}

%token SQRT NUMBER string POW FLOOR ABS

%%
s : sq {printf("Square root of number= %d\n", $1); return 0;}
    |abss {printf("Absolute Value of number= %d\n", $1); return 0;}
    |flr {printf("Floor of number= %d\n", $1); return 0;}
    | pow{printf("Power of number = %d\n",$1); return 0;};

sq : SQRT '(' NUMBER ')' {$$=sqrt($3);};
abss : ABS '('NUMBER')' {$$=abs($3);} |ABS '(''-'NUMBER')' {$$=abs($4);};
flr : FLOOR '('dec')' {$$=floor($3);};
pow: POW '(' NUMBER ',' NUMBER')' {$$=pow($3,$5);} ;
dec: NUMBER'.'NUMBER;



%%


int main() {
    printf("Enter the expression\n");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
	printf(" ERROR:%s \n",s);
}



  ```





