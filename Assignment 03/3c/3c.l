INTEGER [0-9]+
REAL [0-9]*"."[0-9]+
DATATYPE "int"|"float"|"double"|"long"|"void"|"char"|"const"|"string"|"struct"
KEYWORDS "break"|"continue"|"main"|"typedef"|"return"|"exit"|"printf"|"scanf"|"struct"
CONDITIONAL "if"|"else"|"else if"|"switch"|"case"
ITERATIVE "for"|"while"|"do"
ARGUMENTS "argc"|"argv"
PREPROCESSOR #.* 
ARROWOPERATOR "->"
ARITHMETIC_OPERATOR "+"|"-"|"/"|"%"|"*";
LOGICAL_OPERATOR "&&"|"||"|"!"|"!="
RELATIONAL_OPERATOR "<"|">"|"<="|">="|"=="
UNARY "++"|"--"
FORMAT_PROCESSOR "%d"|"%s"|"%c"|"%l"|"%f"|"%d %d"
ACCESS "public"|"private"|"protected"
FUNCTION [a-zA-Z_][a-zA-Z0-9_]*\(
SC ";"
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
COMMA ","
COMMENT "//".*" "*
MULTICOMMENT \/\*(.*\n)*.*\*\/

%%

[ \n\t]+ ;
{INTEGER}              {fprintf(yyout," %s\t\t--- INT\n",yytext);}
{REAL}                {fprintf(yyout," %s\t\t--- FLOAT\n",yytext);}
{SC}                  {fprintf(yyout," %s\t\t--- DELIMITER\n",yytext);}
{CONDITIONAL}         {fprintf(yyout," %s\t\t--- CONDITIONAL\n",yytext);}
{ITERATIVE}           {fprintf(yyout," %s\t\t--- ITERATIVE CONSTRUCT\n",yytext);}
{DATATYPE}            {fprintf(yyout," %s\t\t--- DATATYPE\n",yytext);}
{ACCESS}              {fprintf(yyout," %s\t\t--- ACCESS SPECIFIER\n",yytext);}
{KEYWORDS}            {fprintf(yyout," %s\t\t--- KEYWORDS\n",yytext);}
{IDENTIFIER}          {fprintf(yyout," %s\t\t--- IDENTIFIER\n",yytext);}
{PREPROCESSOR}        {fprintf(yyout," %s\t\t--- PREPROCESSOR\n",yytext);}
{COMMA}               {fprintf(yyout," %s\t\t--- COMMA\n",yytext);}
{UNARY}               {fprintf(yyout," %s\t\t--- UNARY OPERATOR\n",yytext);}
{FORMAT_PROCESSOR}    {fprintf(yyout," %s\t\t--- FORMAT PROCESSOR\n",yytext);}
{ARITHMETIC_OPERATOR} {fprintf(yyout," %s\t\t--- ARITHMETIC OPERATOR\n",yytext);}
{LOGICAL_OPERATOR}    {fprintf(yyout," %s\t\t--- LOGICAL OPERATOR\n",yytext);}
{ARROWOPERATOR}    	  {fprintf(yyout," %s\t\t--- ARROW OPERATOR\n",yytext);}
{RELATIONAL_OPERATOR} {fprintf(yyout," %s\t\t--- RELATIONAL OPERATOR\n",yytext);}
{COMMENT}|{MULTICOMMENT}             {fprintf(yyout," %s\t\t--- COMMENT\n",yytext);}
"="                   {fprintf(yyout," %s\t\t--- ASSIGNMENT OPERATOR\n",yytext);}
"{"                   {fprintf(yyout," %s\t\t--- BLOCK BEGIN\n",yytext);}
"}"                   {fprintf(yyout," %s\t\t--- BLOCK END\n",yytext);}
"("                   {fprintf(yyout," %s\t\t--- PARANTHESIS BEGIN\n",yytext);}
")"                   {fprintf(yyout," %s\t\t--- PARENTHESIS END\n",yytext);}
. 					;


%%

int yywrap()
{
	return 1;
}

int main()
{
	extern FILE *yyin, *yyout;

	yyin = fopen("3c_inputCode.c","r");

	yyout = fopen("3c_outputFile.txt","w");

	yylex();

	fclose(yyin);
	fclose(yyout);
    printf("\n -> Output generated in the file! \n");
	return 0;
}
