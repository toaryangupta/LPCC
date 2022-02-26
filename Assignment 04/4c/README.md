<h2>
  
  [ To recognize valid variable name using YACC tool  ](/Assignment%2004/4b)
  
</h2>


<div class="img">
  <li>Running the files </li>
  <img src="https://user-images.githubusercontent.com/99306046/155846626-eb5975c4-eec9-4152-af1f-9c73f7cf39b6.png "/>



</div>

<h3> Lex File- 4c.l</h3>

```lex
%{
#include<stdio.h>
#include"y.tab.h"

%}
%%

[A-Za-z]    return L;
[0-9]       return N;
"_"         return U;
\n          return 0;
.           return yytext[0];

%%
int yywrap()
{
    return 1;
}             
                  
```

<h3> Yacc File- 4c.y</h3>

```yacc
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

  ```
