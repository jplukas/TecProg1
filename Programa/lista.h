/* LISTA LIGADA SIMPLES GENERICA */

#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_CHAVE 10

/* ESTRUTURAS */
/* Elo da lista */
typedef struct elo {
	struct elo * next;
	void * val;
	union{
		int n;
		char str[TAM_CHAVE];
	}chave;
} elo;

typedef elo* Elo;

/* Lista */
typedef struct {
	Elo cabec;

	/* Funcao para comparar elementos dentro da lista */
	/* Comportamento: */
	/* Retorna -1 para arg1 < arg2 */
	/* Retorna 0 para arg1 == arg2 */
	/* Retorna 1 para arg1 > arg2 */
	int (*comp)(void*, void*);			

	/* Funcao para mostrar conteudo dos elementos da lista */
	/* Usado para testes e afins */
	void (*mostra)(void*);	

	Elo (*insere)(void*, void*);	

} lista;

typedef lista* Lista;

/* FUNCOES */

/* Cria lista vazia e devolve o endereco da tal lista */
/* Recebe uma funcao de comparacao e uma funcao para exibicao dos elementos */
/* Tais funcoes sao necessarias porque a lista e generica */
Lista criaLista(int (*comp)(void*, void*), void(*mostra)(void*), int(*insere)(void*, void*)){
	Lista l = malloc(sizeof(lista));
	l->cabec = NULL;
	l->comp = comp;
	l->mostra = mostra;
	l->insere = insere;
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


int insereNaLista(Lista l, void *val, void* chave){
	Elo e = l->insere(val, chave);
	if(!l->cabec){
		l->cabec = e;
		return 1;
	} 
	Elo el = l->cabec;
	while(el->next) el = el->next;
	el->next = e;
	return 1;
}

void *buscaNaLista(Lista l, void *chave){
	Elo e = l->cabec;
	while(e){
		mostra();
		if(l->comp(chave, e)) return e->val;
		e = e->next;
	}
	return NULL;
}

void *retiraDaLista(Lista l, void *chave){
	if(!chave) return NULL;
	Elo e = l->cabec;
	Elo ant = NULL;
	while(e){
		if(l->comp(chave, e) == 0){
			if(ant) ant->next = e->next;
			else l->cabec = e->next;
			void * val = e->val;
			free(e);
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
		i++;
		mostra(e);
		e = e->next;
	}
	printf("\nNúmero de itens na lista: %d\n", i);
}



#endif /* LISTA_H */