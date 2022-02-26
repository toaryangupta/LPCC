<h2>Build a lexer, using LEX, for finding how much the given document say A is related to another document B  (Hint: ignoring words like "is, am, a , the , if, etc." in document A,  store the remaining words and search these words in document B. Decide on a criteria, that if say 40 % words in A exist in B then both are similar. </h2>

<hr>
<h3> Code </h3>

```lex

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

```
<hr>
<h3> DocA.txt </h3>

```txt

When compared with Python, Java kind of fits between C++ and Python. The programs are written in Java typically run faster than corresponding Python programs and slower than C++. Like C++, Java does static type checking, but Python does not.
```

<hr>
<h3> DocB.txt </h3>

```txt

When compared with C++, Java codes are generally more maintainable because Java does not allow many things which may lead to bad/inefficient programming if used incorrectly. 

```
<hr>
<h3> Output </h3>

![image](https://user-images.githubusercontent.com/99306046/155849117-7bac1d98-f198-43a0-b91f-8542d3749604.png)
