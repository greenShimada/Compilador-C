#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "lexicHeader.h"
#include "sintaticHeader.h"
#include "pilha.h"

Token token;
FILE *file;

void erro(int line) {
	printf(">> Erro sintatico na linha %d\n", line);
	exit(1);
}

void reconhecer(int tok) {
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
      printf("\n resultado da operacao = %d\n\t", topo());
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
   
    char opAux = token.value;
    reconhecer(TOKEN_OPERATOR_BASIC);
    T();
    executaCalculo(opAux);
    E_linha();
  }
  else ;

}

void T_linha(){
  
  if (token.type == TOKEN_OPERATOR){
    char opAux = token.value;
    reconhecer(TOKEN_OPERATOR);    
    F();
    
    executaCalculo(opAux);
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
    printf("%d", token.tokenVal);
    push(token.tokenVal);
    reconhecer(TOKEN_NUMBER);
  }
  else;
}

void executaCalculo(char operator)
{
    int a, b;
    a = pop();
    b = pop();
    printf("%c ", operator);
    switch (operator)
    {
    case '+':
        push(a + b);
        break;
    case '-':
        push(b - a);
        break;
    case '*':
        push(a * b);
        break;
    case '/':
        push(b / a);
        break;
    }
}
