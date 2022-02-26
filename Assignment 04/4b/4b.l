%{
/* Definition section*/
#include "y.tab.h"

%}

%%
sqrt { return SQRT;}
pow {return POW;}
floor {return FLOOR;}
abs {return ABS;}
[0-9]+ {yylval=atoi(yytext); return NUMBER;}

[a-zA-Z]+ { return string; }
[ \t]+ ; /*For skipping whitespaces*/
\n { return 0; }
. { return yytext[0];}

%%


int yywrap()
{
	return 1;
}