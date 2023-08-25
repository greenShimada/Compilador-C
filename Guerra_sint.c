#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "lexicHeader.h"
#include "sintaticHeader.h"

Token token;
FILE *file;

void erro(int line) {
	printf(">> Erro sintatico na linha %d\n", line);
	exit(1);
}

void reconhecer(int tok) {
  printf("\n tipo de token = %d\n", token.type);
	if (tok == token.type)
	  token = Guerra_analyser(file);
	else 
	  erro(token.line);   
}

int main() {

  file = fopen("codigo.txt", "r");
  int c = 0;

  while (c = getc(file), c != EOF){
    ungetc(c, file);
    token = Guerra_analyser(file);

    if (token.type != TOKEN_BREAKLINE){
      if (token.type == TOKEN_INVALID)
        {
        printf("\nErro lexico na linha %d, -> %c <- nao e um caractere valido\n", token.line, token.value);
        exit(1);
        }
      E();
      if (token.type != TOKEN_ENDLINE) erro(token.line);
      printf("\n tipo de token = %d\n\t", token.type);
    }
  }
}

void E(){
  T();
  E_linha();
}

void T(){
  F();
  T_linha();
}

void E_linha(){
  if (token.type == TOKEN_OPERATOR_BASIC){
   
    reconhecer(TOKEN_OPERATOR_BASIC);
    T();
    E_linha();
  }
  else ;

}

void T_linha(){
  
  if (token.type == TOKEN_OPERATOR){
   
    reconhecer(TOKEN_OPERATOR);
    F();
    T_linha();
  }
  else;
}

void F(){
  if (token.type != TOKEN_NUMBER){
    if (token.type == TOKEN_OPEN_PARENTHESES){
      
      reconhecer(TOKEN_OPEN_PARENTHESES);
    }
    E();
    if (token.type == TOKEN_CLOSE_PARENTHESES){
      
      reconhecer(TOKEN_CLOSE_PARENTHESES);
    }
  }

  else if (token.type == TOKEN_NUMBER){
    reconhecer(TOKEN_NUMBER);
  }
  else;
}

