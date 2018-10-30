#ifndef TABSIM_H
#define TABSIM_H
#include "lista.h"

typedef struct {
	Lista * l;
	int tam;
}tabSim;

typedef tabSim* TabSim;

TabSim criaTabSim(int tam, int (*comp)(void*, void*), void(*mostra)(void*)){
	TabSim t = malloc(sizeof(TabSim));
	t->l = malloc(tam * sizeof(Lista));
	for(int i = 0; i < tam; i++) t->l[i] = criaLista(comp, mostra);
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

int insereNaTabSim(TabSim t, char *n, void *val){
	int nHash = funcHash(n, t->tam);
	insereNaLista(t->l[nHash], val);
	return 1;
}

void *buscaNaTabSim(TabSim t, char *n){
	int nHash = funcHash(n, t->tam);
	return (buscaNaLista(t->l[nHash], n));
}

#endif