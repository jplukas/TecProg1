#ifndef LISTA_H
#define LISTA_H

#include "elemento.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Estruturas de dados
//Lista
typedef struct elo {
struct elo * next;
Elemento * val;
} elo;
typedef elo* Elo;

typedef struct {
Elo cabec;
} lista;
typedef lista* Lista;

//Funcoes
//Lista
Lista criaLista(){
	Lista l = malloc(sizeof(Lista));
	l->cabec = NULL;
	return l;
}

void destroiLista(Lista l){
	Elo e = l->cabec;
	Elo proxE;
	while(e){
		proxE = e->next;
		free(e);
		e = proxE;
	}
	l->cabec = NULL;
}

Lista insereNaLista(Lista l, Elemento *val){
	Elo e = l->cabec;
	if(!e){
		l->cabec = malloc(sizeof(Elo));
		l->cabec->val = val;
		return l;
	}
	while(e->next){
		if(strcmp(e->val->n, val->n)) return NULL;
		e = e->next;
	}
	if(strcmp(e->val->n, val->n)) return NULL;
	e->next = malloc(sizeof(Elo));
	e->next->val = val;
	return l;
}

Elemento *buscaNaLista(Lista l, char *n){
	Elo e = l->cabec;
	while(e){
		if(strcmp(e->val->n, n)) return e->val;
		e = e->next;
	}
	return NULL;
}

Elemento *retiraDaLista(Lista l, Elemento *val){
	if(!val) return NULL;
	Elo e = l->cabec;
	Elo ant = NULL;
	while(e){
		if(e->val == val){
			if(ant) ant->next = e->next;
			else l->cabec = e->next;
			free(e);
			e = NULL;
			return val;
		}
		ant = e;
		e = e->next;
	}
	return NULL;
}

void percorreLista(Lista l){
	int i = 0;
	Elo e = l->cabec;
	while(e){
		printf("%s\n", e->val->n);
		i++;
		e = e->next;
	}
	printf("\nNúmero de itens na lista: %d\n", i);
}



#endif /* LISTA_H */