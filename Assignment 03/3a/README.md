<h2>

[ For parts of speech for subset of ENGLISH language without using SYMBOL TABLE. ]()

</h2>
<div class="img">
  <li>Running the files </li>
  <img src="https://user-images.githubusercontent.com/99306046/155844438-d0fd9602-7b73-41aa-920e-ced75b49e10f.png"  />


</div>

<h3> Lex File- 3a.l</h3>

```lex
%{
int lineCount=1;
%}

DIGIT [0-9]
NUMBERS {DIGIT}+
VERBS "listen"|"run"|"play"|"walk"|"sing"|"join"|"gone"|"dance"|"throws"|"catch"|"catching"|"talking"|"talks"|"talk"|"be"|"am"|"is"|"was"|"were"|"being"|"washed"|"Wash"|"wash"|"has"|"have"|"had"|"do"|"does"|"did"|"can"|"could"|"shall"|"should"|"will"|"would"|"may"|"find"|"are" 
ADJECTIVES "fast"|"awesome"|"hilarious"|"fun"|"mature"|"cheerful"|"preventive"|"Preventive"|"slow"|"Slow"|"Great"|"great"|"Good"|"good"|"bad"|"Bad"|"Worse"|"Worst"|"Best"|"best"|"better"|"worse"|"worst"|"funny"|"difficult"|"easy"|"Easy"|"Difficult"|"clean"|"dirty"|"colourful"|"white"|"red"|"pink"|"violet"|"indigo"|"purple"|"grey"
ADVERBS "lovingly"|"happily"|"carefully"|"cheerfully"|"carelessly"|"sadly"|"honestly"|"steadily"|"readily"|"immediately"|"gently"|"slowly"|"very"
PRONOUNS "you"|"us"|"I"|"she"|"She"|"It"|"it"|"her"|"his"|"His"|"Her"|"He"|"he"|"they"|"They"|"this"|"This"
CONJUNCTIONS "after"|"although"|"as"|"as if"|"as long as"|"as much as"|"as soon as"|"as though"|"because"|"before""by the time"|"even if"|"even though"|"if"|"in order that"|"in case"|"in the event that"|"now that"|"once"|"only"|"only if"|"provided that"|"since"|"so"|"supposing"|"that"|"than"|"though"|"till"|"unless"|"until"|"when"|"whenever"|"where"|"whereas"|"wherever"|"whether or not"|"while"|"and"|"or"
PREPOSITIONS "in"|"on"|"to"|"under"|"over"|"above"|"below"|"beside"|"towards"|"out"|"of"
GERUNDS "having"|"doing"|"going"
ARTICLES "the"|"an"|"a"


%%
[ \t]+ ;
\n              {lineCount++;fprintf(yyout," Line : %d\n",lineCount);}
{NUMBERS}       {fprintf(yyout," - %s\t\t\t---- NUMBER\n",yytext);}
{VERBS}         {fprintf(yyout," - %s\t\t\t---- VERB\n",yytext);}
{ADVERBS}       {fprintf(yyout," - %s\t\t\t---- ADVERB\n",yytext);}
{PRONOUNS}      {fprintf(yyout," - %s\t\t\t---- PRONOUN\n",yytext);}
{CONJUNCTIONS}  {fprintf(yyout," - %s\t\t\t---- CONJUNCTION\n",yytext);}
{PREPOSITIONS}  {fprintf(yyout," - %s\t\t\t---- PREPOSITION\n",yytext);}
{ARTICLES}      {fprintf(yyout," - %s\t\t\t---- ARTICLE\n",yytext);}
{ADJECTIVES}    {fprintf(yyout," - %s\t\t\t---- ADJECTIVE\n",yytext);}
{GERUNDS}       {fprintf(yyout," - %s\t\t\t---- GERUND\n",yytext);}
[a-zA-Z]+       {fprintf(yyout," - %s\t\t\t---- NOUN\n",yytext);}
\.              {fprintf(yyout," - %s\t\t\t---- FULLSTOP\n",yytext);}

%%

int yywrap()
{
	return 1;
}

int main()
{
	extern FILE *yyin, *yyout;
	yyin = fopen("3a_inputFile.txt","r");
	yyout = fopen("3a_outputFile.txt","w");
	yylex();
	printf("\noutput generated in file!\n");
	fclose(yyin);
	fclose(yyout);
	return 0;
}
```
<h3> 
  Input File- 3a_inputFile.txt

</h3>

```txt

They are awesome and hilarious.
Dave should join them.

```

<h3>
  
  Output File-  3a_outputFile.txt

</h3>

```txt
 - They			---- PRONOUN
 - are			---- VERB
 - awesome			---- ADJECTIVE
 - and			---- CONJUNCTION
 - hilarious			---- ADJECTIVE
 - .			---- FULLSTOP

 Line : 2
 - Dave			---- NOUN
 - should			---- VERB
 - join			---- VERB
 - them			---- NOUN
 - .			---- FULLSTOP

```



