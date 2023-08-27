#ifndef PILHA_HEADER_H
#define PILHA_HEADER_H

#define MAX 10000

int vetorPilha[MAX];
int a, b;
int tam = 0;

int pop(){
    return vetorPilha[--tam];
}
void push(int a){
    vetorPilha[tam++] = a;
}
int topo(){
    return vetorPilha[tam];
}

#endif