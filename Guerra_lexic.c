#include "lexicHeader.h"

static int line = 1;

Token Guerra_analyser(FILE *arquivo)
{
    Token activeToken;
    char activeChar = getc(arquivo);

    while (isspace(activeChar)  && activeChar !='\n')
        activeChar = getc(arquivo);

    while (activeChar != EOF)
    {
        activeToken.line = line;
        if (isdigit(activeChar))
        {
            int value = activeChar - '0';
            activeChar = getc(arquivo);

            while (isdigit(activeChar))
            {
                value = value * 10 + (activeChar - '0');
                activeChar = getc(arquivo);
            }
            ungetc(activeChar, arquivo); 
            activeToken.tokenVal = value;
            activeToken.type = TOKEN_NUMBER;
          
            return activeToken;
        }
        else if (activeChar == '*' || activeChar == '/')
        {
            activeToken.type = TOKEN_OPERATOR;
            activeToken.value = activeChar;
            return activeToken;
        }
        else if (activeChar == '+' || activeChar == '-')
        {
            activeToken.type = TOKEN_OPERATOR_BASIC;
            activeToken.value = activeChar;
            return activeToken;
        }
        else if (activeChar == ';')
        {
            activeToken.type = TOKEN_ENDLINE;
            activeToken.value = activeChar;
            return activeToken;
        }
        else if (activeChar == '\n')
        {
            line += 1;
            activeToken.type = TOKEN_BREAKLINE;
            activeToken.value = activeChar;
            return activeToken;
        }
        else if (activeChar == '(')
        {
            activeToken.type = TOKEN_OPEN_PARENTHESES;
            activeToken.value = activeChar;
            return activeToken;
        }
        else if (activeChar == ')')
        {
            activeToken.type = TOKEN_CLOSE_PARENTHESES;
            activeToken.value = activeChar;
            return activeToken;
        }

        else{
            activeToken.type = TOKEN_INVALID;
            activeToken.value = activeChar;
            return activeToken;
        }
        
    }
    activeToken.type = TOKEN_EOF;
    return activeToken;
}



