#!/bin/bash
flex -o analex.c analex.l &&
yacc -o mycomp.c mycomp.y -d &&
gcc mycomp.c -o mycomp.exe &&
./mycomp.exe teste2.c &&
echo "Saída do MARS:"  #&&
#java -jar Mars.jar saida.asm


