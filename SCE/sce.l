%{
#include<stdio.h>
#include <string.h>

struct word
{
    char string[100];
};
struct word store[101];

int ind = 0,count=0;

void StoringWords(char words[])
{
	strcpy(store[ind].string,words);
        ind++;	
}

void check()
{
        int i = 0;
        char temp[20];
        FILE *fp;
        fp=fopen("DocB.txt", "r");
	 while((fscanf(fp, "%s", temp))!=EOF)
	 {
		for(i=0;i<ind;i++)
        	{
			if(!(strcmp(store[i].string,temp)))
			{
				count++;
			}
		}
		
	 }
}

%}
%%

is |
the |
and |
am |
a |
of |
it |
to |
in ;
. ; 
([a-zA-Z0-9])*  {StoringWords(yytext);}

%%

int yywrap() 
{ 
    return 1; 
}

int main() 
{ 
    extern FILE *yyin; 
    yyin=fopen("DocA.txt","r");
    yylex(); 
    check();
    float percent = (count*100)/ind;
    if(percent>=40) 
    {
        printf("Document A similar to Document B\n");
        printf("Percentage of Similarity: %.2f \n", percent);
    }
    else 
    {
        printf("Document A and B are Different\n");
        printf("Percentage of Similarity: %.2f \n", percent);
    }

    return 0;
}
