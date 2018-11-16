#include "lista_fptr.h"

typedef struct eloFptr{
	struct eloFptr* prox;
	char* chave;
	unsigned short int (*fptr)(void*, void*);
}eloFptr;

typedef struct listaFptr{
	eloFptr* inicio;
}listaFptr;

ListaFptr criaListaFptr(){
	listaFptr* lista = malloc(sizeof(listaFptr));
	lista->inicio = NULL;
	return (ListaFptr)lista;
}

unsigned short int destroiListaFptr(ListaFptr l){
	if(!l) return 0;
	eloFptr* elo = ((listaFptr*)l)->inicio;
	while(elo){
		eloFptr* prox = elo->prox;
		free(elo->chave);
		elo->chave = NULL;
		elo->fptr = NULL;
		elo = prox;
	}
	free(l);
	return 1;
}

unsigned short int insereListaFptr(ListaFptr l, char* chave, unsigned short int (*acao)(void*, void*)){
	if(!l || !chave || !acao) return 0;
	listaFptr* lista = (listaFptr*)l;
	eloFptr* novo = malloc(sizeof(eloFptr));
	novo->chave = malloc((strlen(chave) + 1) * sizeof(char));
	strcpy(novo->chave, chave);
	novo->prox = NULL;
	novo->fptr = acao;
	if(!lista->inicio){
		lista->inicio = novo;
		return 1;
	}
	eloFptr* this = lista->inicio;
	while(this->prox) this = this->prox;
	this->prox = novo;
	return 1;
}

unsigned short int(*buscaListaFptr(ListaFptr l, char* chave))(void*, void*){
	if(!l || !chave) return NULL;
	eloFptr* elo = ((listaFptr*)l)->inicio;
	while(elo && (strcmp(elo->chave, chave) != 0)) elo = elo->prox;
	if(elo)	return elo->fptr;
	return NULL;
}

unsigned short int(*retiraListaFptr(ListaFptr l, char* chave))(void*, void*){
	if(!l || !((listaFptr*)l)->inicio || !chave) return NULL;
	eloFptr* elo = ((listaFptr*)l)->inicio;
	unsigned short int(*fptr)(void*, void*) = NULL;
	if(strcmp(chave, ((listaFptr*)l)->inicio->chave) == 0){
		((listaFptr*)l)->inicio = elo->prox;
		fptr = elo->fptr;
		free(elo->chave);
		elo->chave = NULL;
		elo->fptr = NULL;
		elo->prox = NULL;
		free(elo);
	}
	else{
		eloFptr* ant = elo;
		while(elo && (strcmp(elo->chave, chave) != 0)){
			ant = elo;
			elo = elo->prox;
			fptr = ant->fptr;
			free(ant->chave);
			ant->chave = NULL;
			ant->fptr = NULL;
			ant->prox = NULL;
			free(ant);
		}
	}
	return fptr;
}

void percorreListaFptr(ListaFptr l){
	if(!l) return;
	eloFptr* this = ((listaFptr*)l)->inicio;
	while(this) printf("%s\n", this->chave);
}