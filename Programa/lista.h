#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct lista* Lista;

Lista criaLista(int (*destroi)(void*), void (*mostra)(void*));

int destroiLista(Lista l);

int insere(Lista l, char* chave, void* valor);

void* busca(Lista l, char* chave);

void* retira(Lista l, char* chave);

void percorre(Lista l);

#endif /* LISTA_H */