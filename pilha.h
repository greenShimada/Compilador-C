#ifndef PILHA_HEADER_H
#define PILHA_HEADER_H

#define MAX 1000

int PILHA[MAX];
int size = 0;

int pop(){
    return PILHA[--size];
}

void push(int value){
    PILHA[size++] = value;
}

int topo(){
    return PILHA[size - 1];
}

#endif