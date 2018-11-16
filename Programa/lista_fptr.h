#ifndef LISTA_FPTR_H
#define LISTA_FPTR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct listaFptr* ListaFptr;

ListaFptr criaListaFptr();

unsigned short int destroiListaFptr(ListaFptr l);

unsigned short int insereListaFptr(ListaFptr l, char* chave, unsigned short int (*acao)(void*, void*));

unsigned short int(*buscaListaFptr(ListaFptr l, char* chave))(void*, void*);

unsigned short int(*retiraListaFptr(ListaFptr l, char* chave))(void*, void*);

void percorreListaFptr(ListaFptr l);

#endif /* LISTA_FPTR_H */