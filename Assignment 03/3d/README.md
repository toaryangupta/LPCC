<h2>

[ For parts of speech for subset of ENGLISH language without using SYMBOL TABLE. ](/Assignment%2003/3d)

</h2>

<div class="img">
  
  <li>Running the files </li>
  <img src="https://user-images.githubusercontent.com/99306046/155845096-fd68479e-f17b-4646-bef4-381bc0b42117.png"  "/>

</div>

<h3> Lex File- 3d.l</h3>

```lex
%{

enum 
{
    LOOKUP = 0,
    INT,
    FLOAT,
    TEXT,
    CHAR,
    KEYWORD,
    ARGUMENT,
    DATATYPE,
    CONDITIONAL_KEY,
    ITERATIVE_KEY,
    ARITHEMATIC_OPERATOR,
    LOGICAL_OPERATOR,
    RELATIONAL_OPERATOR,
    IDENTIFIER,
    UNARY_OPERATOR,
    FORMAT_PROCESSOR,
    FUNCTION,
    ACCESS_MODIFIER,
    DELIMITER,
    COMMA,
    INVERTED_COMMAS,
    PARANTHESIS,
    BLOCK,
    BRACKET,
    ASSIGNMENT_OPERATOR
};

int state;

int addWord(int type, char *word);
int lookupWord(char *word);

%}

%%
\n    { state = LOOKUP; }
^INT { state = INT; }
^FLOAT { state = FLOAT; }
^text { state = TEXT; }
^CHAR { state = CHAR; }
^keyword { state = KEYWORD; }
^argument { state = ARGUMENT; }
^datatype { state = DATATYPE; }
^conditional { state = CONDITIONAL_KEY; }
^iterative { state = ITERATIVE_KEY; }
^arithematic { state = ARITHEMATIC_OPERATOR; }
^logical { state = LOGICAL_OPERATOR; }
^relational { state = RELATIONAL_OPERATOR; }
^identifier { state = IDENTIFIER; }
^unary { state = UNARY_OPERATOR; }
^format { state = FORMAT_PROCESSOR; }
^function { state = FUNCTION; }
^access { state = ACCESS_MODIFIER; }
^delimiter { state = DELIMITER; }
^comma { state = COMMA; }
^inverted_commas { state = INVERTED_COMMAS; }
^paranthesis { state = PARANTHESIS; }
^block { state = BLOCK; }
^bracket { state = BRACKET; }
^assignment { state = ASSIGNMENT_OPERATOR; }

[a-zA-Z1-9]+ {
           if(state != LOOKUP) {
                addWord(state, yytext);
              } else {
                 switch(lookupWord(yytext)) 
                 {
                 	case INT: printf("%s: int\n", yytext); break;
                 	case FLOAT: printf("%s: float\n", yytext); break;
                 	case TEXT: printf("%s: text\n", yytext); break;
                 	case CHAR: printf("%s: char\n", yytext); break;
                 	case KEYWORD: printf("%s: keyword\n", yytext); break;
                 	case ARGUMENT: printf("%s: argument\n", yytext); break;
                 	case DATATYPE: printf("%s: datatype\n", yytext); break;
                 	case CONDITIONAL_KEY: printf("%s: conditional keyword\n", yytext); break;
                 	case ITERATIVE_KEY: printf("%s: iterative keyword\n", yytext); break;
                 	case ARITHEMATIC_OPERATOR: printf("%s: arithematic operator\n", yytext); break;
                 	case LOGICAL_OPERATOR: printf("%s: logical operator\n", yytext); break;
                 	case RELATIONAL_OPERATOR: printf("%s: relational operator\n", yytext); break;
                 	case IDENTIFIER: printf("%s: identifier\n", yytext); break;
                 	case UNARY_OPERATOR: printf("%s: unary operator\n", yytext); break;
                 	case FORMAT_PROCESSOR: printf("%s: format processor\n", yytext); break;
                 	case FUNCTION: printf("%s: function\n", yytext); break;
                 	case ACCESS_MODIFIER: printf("%s: access modifier\n", yytext); break;
                 	case DELIMITER: printf("%s: delimiter\n", yytext); break;
                 	case COMMA: printf("%s: comma\n", yytext); break;
                 	case INVERTED_COMMAS: printf("%s: inverted commas\n", yytext); break;
                 	case PARANTHESIS: printf("%s: parathesis\n", yytext); break;
                 	case BLOCK: printf("%s: block\n", yytext); break;
                 	case BRACKET: printf("%s: bracket\n", yytext); break;
                 	case ASSIGNMENT_OPERATOR: printf("%s: assignment operator\n", yytext); break;
                 	default: printf("%s: don't recognize\n", yytext); break;
                 }
          }
         }

.    /* ignore anything else */ ;

%%


void main()
{
    yylex();
}

struct word {
      char *wordName;
      int wordType;
      struct word *next;
};

struct word *wordList;

extern void *malloc() ;

int addWord(int type, char *word)
{
      struct word *wp;

      if(lookupWord(word) != LOOKUP) {
            printf("!!! warning: word %s already defined \n", word);
            return 0;
      }

      wp = (struct word *) malloc(sizeof(struct word));

      wp->next = wordList;

      wp->wordName = (char *) malloc(strlen(word)+1);
      strcpy(wp->wordName, word);
      wp->wordType = type;
      wordList = wp;
      return 1; 
}

int lookupWord(char *word)
{
      struct word *wp = wordList;
      for(; wp; wp = wp->next) {
      if(strcmp(wp->wordName, word) == 0)
            return wp->wordType;
      }

      return LOOKUP; 
}

```



