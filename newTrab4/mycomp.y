%union {
  struct no {
    int place;
	char *code;
  } node;
  int place;
}
%{ 
#include "analex.c" 
#include "codigo.h"
%}
%token <place> NUM 
%token <place> ID 
%token AND
%token OR 
%token NOT
%token EQ
%token LE
%token GE
%token NE
%token IF
%token WHILE
%token ELSE
%token DO
%token INT
%token READ
%token PRINTLN
%token PRINT
%token CHAR
%token VOID
%left AND OR
%left '>' '<' NE EQ GE LE
%left '+' '-'
%left '*' '/'

%type <node> Exp Atribuicao

%start Prog
%%
Prog : Funcao
	| Funcao Prog
	;
	
Funcao:
    Tipo_f ID '(' Declps ')' '{' Decls Statement_Seq '}' 
   ;
   
Declps :
	Ldeclps
	|
	;
	
Ldeclps :
	  Tipo ID  
	| Ldeclps ',' Tipo ID 
	;
     
Tipo_f :
	VOID
	| Tipo
	|
	;

Decls :
	Decl Decls
	|
	;
	
Decl :
	Tipo Vars ';'
	;
	
Vars:
	ID ',' Vars 
	| ID        
	;

Tipo :
	INT
	| CHAR
	;
			
	
Statement_Seq:
	Statement				   
	| Statement_Seq Statement  
    
Args:
	  Exp ',' Args
	| Exp
	|
	;
		
Statement: 
		Atribuicao
	|	If_Statement
	| 	While_Statement
	|   Do_While_Statement
	|   ID '(' Args ')' ';'
	|	PRINT '(' Exp ')' ';' 
	|   PRINTLN '(' Exp ')' ';' { /*Println($3);*/}
	|   ID '=' READ '(' ')' ';' { /* Read($1); */ }
	;
	
	
Atribuicao : ID '=' Exp ';'  { Atrib(&$$,$1,$3); printf("%s", $$.code);}
	;

Compound_Statement :
	  Statement
	| '{' Statement_Seq '}'
	;
	
If_Statement:
	  IF '(' Exp ')' Compound_Statement Else_Part
	;
		
Else_Part:
	  ELSE Compound_Statement
	|
	;
		
While_Statement:
	  WHILE '(' Exp ')' Compound_Statement  
	;

Do_While_Statement:
	  DO Compound_Statement WHILE '(' Exp ')' ';'   
	;
			
Exp : Exp '+' Exp  { /* $$ = newTemp(); ExpAri("add",$$,$1,$3); */}
	| Exp '-' Exp  
	| Exp '*' Exp  
	| Exp '/' Exp  
	| Exp '>' Exp 
	| Exp '<' Exp  
	| Exp GE Exp   
	| Exp LE Exp   
	| Exp EQ Exp   
	| Exp NE Exp   
	| Exp AND Exp  
	| Exp OR Exp   
	| '(' Exp ')'  { }
	| NUM	  {  $$.place = newTemp(); Li(&$$,$1); } 
				 		   
	| ID      {  	}     
	;   
	
%%  
int main(int argc, char **argv) {   
  freopen("saida.asm","w",stdout);	
  printf(".text\n");
  yyin = fopen(argv[1],"r");
  yyparse();
    
} 



