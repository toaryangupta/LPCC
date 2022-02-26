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