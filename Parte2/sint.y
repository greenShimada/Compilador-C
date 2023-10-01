%{ 
#include "lex.yy.c" 
%}

%token FUNCTION
%token ENDIF
%token PRINT
%token PRINTLN
%token READ
%token CHAR
%token NOT
%token NUM 
%token ID 
%token AND
%token OR 
%token EQ
%token LE
%token GE
%token NE
%token IF
%token WHILE
%token ELSE
%token DO
%token INTEGER
%left AND OR
%left '>' '<' NE EQ GE LE
%left '+' '-'
%left '*' '/'
%start Prog
%%
Prog : Statement_Seq
	;
	
	
Statement_Seq :
	Statement Statement_Seq
	|
	;
	
Args:
	  Args ',' Exp
	| Exp
	|
	;
		
Statement: 
		Atribuicao
	|	If_Statement
	| 	While_Statement
	|   Do_While_Statement
	|   ID '(' Args ')' ';'
	|   PRINT Exp ';'
	|	PRINTLN Exp ';' '\n'
	|	READ INTEGER
	| 	Function_Statement
	;

Function_Statement: FUNCTION ID '(' Args ')' Compound_Statement ';'
	;
	
Atribuicao : ID '=' Exp ';' 
	| INTEGER ID '=' Exp ';'
	| CHAR ID '=' Exp ';'

	;

Compound_Statement :
	  Statement
	| '{' Statement_Seq '}'
	;
	
If_Statement:
	  IF '(' Exp ')' Compound_Statement Else_Part ENDIF
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
			
Exp : Exp '+' Exp  
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
	| '(' Exp ')'  
	| NUM		   
	| ID           
	;   

%%  
int main(int argc, char **argv) {     
  yyin = fopen(argv[1],"r");
  yyparse();      
} 


