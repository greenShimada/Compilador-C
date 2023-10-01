#!/bin/bash
flex analex.l &&
yacc -o sint.c sint.y -d &&
gcc sint.c -o resultado.exe &&
./resultado.exe codigo.txt 
