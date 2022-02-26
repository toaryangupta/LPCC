%{
#include<stdio.h>
#include<stdlib.h>
 int yylex();
void yyerror(const char *s);
int flag=0;

%}
%token L N U

%%

v : L alphaNumeric | U alphaNumeric;

alphaNumeric : L alphaNumeric | N alphaNumeric | U alphaNumeric | L | N | U;

%%

int main()
{
    printf("\nEnter a Variable Name: ");
    yyparse();

    if(flag==0){
        printf("\n -> Entered variable name is Correct!\n");
    }
    return 0;   
}

void yyerror(const char *s)
{
    printf("\n -> Entered variable name is Incorrect!\n");
    flag = 1;
}