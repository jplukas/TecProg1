#define NULL 0
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
	Lista l;
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
		if(equals(e->val->n, val->n)) return NULL;
		e = e->next;
	}
	if(equals(e->val->n, val->n)) return NULL;
	e->next = malloc(sizeof(Elo));
	e->next->val = val;
	return l;
}

Elemento *buscaNaLista(Lista l, char *n){
	Elo e = l->cabec;
	while(e){
		if(equals(e->val->n, n)) return e->val;
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


int equals(char *s1, char *s2){
	if(s1 == s2) return 1;
	int i = 0;
	while(!((s1[i] == '\0') && (s2[i] == '\0'))){
		if(s1[i] != s2[i]) return 0;
		i++;
	}
	return 1;
}

int strCopy(char *origem, char *destino){
	int i = 0;
	while(origem[i] != '\0'){
		destino[i] = origem[i];
		i++;
	}
	destino[i] = '\0';
}