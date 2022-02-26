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


