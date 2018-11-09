#ifndef TABSIM_H
#define TABSIM_H
#include "lista.h"

typedef struct {
	Lista * l;
	int tam;
}tabSim;

typedef tabSim* TabSim;

TabSim criaTabSim(int tam, int (*comp)(void*, void*), void(*mostra)(void*),\
 int(*insere)(void*, void*)){
	TabSim t = malloc(sizeof(tabSim));
	t->l = malloc(tam * sizeof(lista));
	for(int i = 0; i < tam; i++) t->l[i] = criaLista(comp, mostra, insere);
	t->tam = tam;
	return t;
}

void destroiTabSim(TabSim t){
	for(int i = 0; i < t->tam; i++){
		destroiLista(t->l[i]);
	}
	free(t);
}

int funcHash(char *s, int tam){
	return 0;
}

int insereNaTabSim(TabSim t, char *chave, void *val){
	int nHash = funcHash(chave, t->tam);
	insereNaLista(t->l[nHash], val, chave);
	return 1;
}

void *buscaNaTabSim(TabSim t, char *chave){
	int nHash = funcHash(chave, t->tam);
	return (buscaNaLista(t->l[nHash], chave));
}

#endif