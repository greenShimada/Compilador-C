%{
#include <stdio.h>
#include "sint.h" 
#include "tabsimb.h" 
int line=1;
int yyerror(char *s) { 
  fprintf(stderr, "%s na linha %d\n",s,line); 
}
%}
%%
"function" {return FUNCTION;}
"end if" {return ENDIF;}
"print" {return PRINT;}
"println" {return PRINTLN;}
"read" {return READ;}
"if"  { return IF; }
"else" { return ELSE;}
"while" { return WHILE;}
"char" { return CHAR;}
"do"  { return DO;}
"integer" { return INTEGER;}
">="  { return GE;}
"<="  { return LE;}
"=="  { return EQ;}
"<>"  { return NE;}
"or"  { return OR;}
"and" { return AND;}
"not"   { return NOT;}
">"   { return '>';}
"<"   { return '<';}
"="   { return '='; }
"+"   { return '+'; }
"-"   { return '-'; }
"*"   { return '*'; }
"/"   { return '/'; }
";"   { return ';'; }
"("   { return '('; }
")"   { return ')'; }
"{"   { return '{'; }
"}"   { return '}'; }
","   { return ','; }


[0-9]+("."[0-9]+)?   { return NUM; }
[a-zA-Z][a-zA-Z0-9]*   { insere(yytext); return ID; }
\        { ; }
\n       { line++;}     
\t       { ; }
"##".*\n { }             
.        { yyerror("illegal token"); }
%%
#ifndef yywrap
int yywrap() { return 1; }
#endif




