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

%type <node> Exp Atribuicao Compound_Statement
%type <node> Statement Statement_Seq If_Statement
%type <node> While_Statement Ldeclps

%start Prog
%%
Prog : Funcao
	| Funcao Prog
	;
	
Funcao:
    Tipo_f ID '(' Declps ')' '{' Decls Statement_Seq '}'  { 
		unsigned short int lblNumber;
		char label[10];
		lblNumber = newLabel();
		sprintf(label, "L%d:", $2);
		char nome[10];
		
		getName($2, nome);
		if (strcmp(nome,"$s0") == 0) {
			printf("\n%s\n%s\tli $v0, 10\n\tsyscall",
	 	label,
	 	$8.code);}
		else
			printf("\n%s\n%s\n\tjr $ra",label,$8.code);
		}
		
   ;
   
Declps :
	Ldeclps
	|
	;
	
Ldeclps :
	  Tipo ID  {	ArgAtrib(&$$, $2); }

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
	Statement				   { create_cod(&$$.code); 
								 insert_cod(&$$.code,$1.code);
							   }
	| Statement_Seq Statement  { create_cod(&$$.code); 
								 insert_cod(&$$.code,$1.code); 
								 insert_cod(&$$.code,$2.code);	
						       }
    
Args:
	  Exp ',' Args
	| Exp
	|
	;
		
Statement: 
		Atribuicao
	|	If_Statement 
	| 	While_Statement {}
	|   Do_While_Statement {}  
	|   ID '(' Args ')' ';' { 
			create_cod(&$$.code); 
			$$.place = $1;
			sprintf(instrucao, "\tjal L%d\n", $$.place);
			insert_cod(&$$.code, instrucao);
			}
	|	PRINT '(' Exp ')' ';' {Print(&$$,$3);}
	|   PRINTLN '(' Exp ')' ';' { Println(&$$,$3);}
	|   ID '=' READ '(' ')' ';' { Read(&$$,$1);  }
	;
	
	
Atribuicao : ID '=' Exp ';'  { Atrib(&$$,$1,$3); }
	;

Compound_Statement :
	  Statement
	| '{' Statement_Seq '}' {$$ = $2;}
	;
	
If_Statement:
	  IF '(' Exp ')' Compound_Statement { If(&$$,$3,$5); }
	| IF '(' Exp ')' Compound_Statement ELSE Compound_Statement  { IfElse(&$$,$3,$5,$7); }
	;
		
While_Statement:
	  WHILE '(' Exp ')' Compound_Statement {
		While(&$$, $3, $5);
		}
	;

Do_While_Statement:
	  DO Compound_Statement WHILE '(' Exp ')' ';'   
	;
			
Exp : Exp '+' Exp  { ExpAri("add",&$$,$1,$3); }
	| Exp '-' Exp  
	| Exp '*' Exp  
	| Exp '/' Exp  
	| Exp '>' Exp  { ExpRel("bgt",&$$,$1,$3);} 
	| Exp '<' Exp  
	| Exp GE Exp   
	| Exp LE Exp   
	| Exp EQ Exp   
	| Exp NE Exp   
	| Exp AND Exp  
	| Exp OR Exp   
	| '(' Exp ')'  { }
	| NUM	  {  $$.place = newTemp(); Li(&$$,$1); } 				 		   
	| ID      {  create_cod(&$$.code); $$.place = $1;	}     
	;   
	
%%  
int main(int argc, char **argv) {   
  freopen("saida.asm","w",stdout);	
  printf(".text\n");
  yyin = fopen(argv[1],"r");
  yyparse();
    
} 



