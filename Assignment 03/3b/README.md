<h2>

[ For parts of speech for subset of ENGLISH language without using SYMBOL TABLE. ]()

</h2>
<div class="img">
  <li>Running the files </li>
  <img src="https://user-images.githubusercontent.com/99306046/155845028-30454901-7c8b-4575-89d3-80bcd6c91666.png"  "/>

</div>

<h3> Lex File- 3b.l</h3>

```lex
%{

enum 
{
    LOOKUP = 0,
    VERB,
    ADJECTIVE,
    ADVERB,
    NOUN,
    PREPOSITION,
    CONJUNCTION,
    PRONOUN
};

int state;

int addWord(int type, char *word);
int lookupWord(char *word);

%}

%%
\n    { state = LOOKUP; }
^verb { state = VERB; }
^adjective  { state = ADJECTIVE; }
^adverb  { state = ADVERB; }
^noun { state = NOUN; }
^preposition { state = PREPOSITION; }
^pronoun { state = PRONOUN; }
^conjunction { state = CONJUNCTION; }


[a-zA-Z]+ {
           if(state != LOOKUP) {
                addWord(state, yytext);
              } else {
                 switch(lookupWord(yytext)) {
                 case VERB: printf("%s: verb\n", yytext); break;
                 case ADJECTIVE: printf("%s: adjective\n", yytext); break;
                 case ADVERB: printf("%s: adverb\n", yytext); break;
                 case NOUN: printf("%s: noun\n", yytext); break;
                 case PREPOSITION: printf("%s: preposition\n", yytext); break;
                 case PRONOUN: printf("%s: pronoun\n", yytext); break;
                 case CONJUNCTION: printf("%s: conjunction\n", yytext); break;
                 default:
                         printf("%s: don't recognize\n", yytext);
                         break;
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




