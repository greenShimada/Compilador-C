#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
    TOKEN_NUMBER,            //0
    TOKEN_OPERATOR,          //1
    TOKEN_INVALID,           //2
    TOKEN_ENDLINE,           //3
    TOKEN_EOF,               //4
    TOKEN_BREAKLINE,         //5
    TOKEN_OPEN_PARENTHESES,  //6
    TOKEN_CLOSE_PARENTHESES, //7
    TOKEN_OPERATOR_BASIC     //8
}TokenType;

typedef struct 
{
   TokenType type;
   char value;
   int tokenVal;
   int line;
}Token;

#endif