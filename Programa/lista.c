#include "lista.h"

typedef struct elo{
	struct elo* next;
	void* valor;
	char* chave;
}elo;

typedef struct lista{
	elo * cabeca;
	int (*destroi)(void*);
	void (*mostra)(void*);
}lista;

//typedef lista* Lista;

Lista criaLista(int (*destroi)(void*), void (*mostra)(void*)){
	Lista l = malloc(sizeof(lista));
	l->cabeca = NULL;
	l->destroi = destroi;
	l->mostra = mostra;
	return l;
}

int destroiLista(Lista l){
	if(!l) return 0;
	elo* e = l->cabeca;
	while(e){
		elo* prox = e->next;
		free(e->chave);
		l->destroi((void*)e->valor);
		free(e);
		e = prox;
	}
	free(l);
	l = NULL;
	if(!l) return 1;
	return 0;
}

int insere(Lista l, char* chave, void* valor){
	if(!l) return 0;
	elo * e = malloc(sizeof(elo));
	if(!e) return 0;
	e->chave = malloc((strlen(chave) + 1) * sizeof(char));
	if(!e->chave) return 0;
	e->valor = valor;
	strcpy(e->chave, chave);
	if(!(l->cabeca)) l->cabeca = e;
	else{
		elo* el = l->cabeca;
		while(el->next) el = el->next;
		el->next = e;
	}
	return 1;
}

void* busca(Lista l, char* chave){
	if(!l){
		printf("LISTA VAZIA!\n");
		return NULL;	
	} 
	elo* e = l->cabeca;
	while(e){
		if(strcmp(e->chave, chave) == 0) return e->valor;
		e = e->next;
	}
	return NULL;
}

void* retira(Lista l, char* chave){
	if(!l){
		printf("LISTA VAZIA!\n");
		return NULL;	
	} 
	elo* e = l->cabeca;
	elo* ant = e;
	if(strcmp(e->chave, chave) == 0){
		void* aux = e->valor;
		l->cabeca = e->next;
		l->destroi(e->valor);
		e->valor = NULL;
		free(e->chave);
		e->chave = NULL;
		free(e);
		e = NULL;
		return aux;
	}
	while(e){
		if(strcmp(e->chave, chave) == 0){
			void* aux = e->valor;
			ant->next = e->next;
			l->destroi(e->valor);
			e->valor = NULL;
			free(e->chave);
			e->chave = NULL;
			free(e);
			e = NULL;
			return aux;
		}
		ant = e;
		e = e->next;
	}
	return NULL;
}

void percorre(Lista l){
	if(!l){
		printf("Lista não existe!\n");
		return;
	}
	int n = 0;
	elo* e = l->cabeca;
	while(e){
		n++;
		printf("Chave: %s\n", e->chave);
		l->mostra(e->valor);
		e = e->next;
	}
	printf("Numero de elementos na lista: %d\n", n);
}