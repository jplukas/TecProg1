#include "lista.h"

typedef struct {
	Lista * l;
	int tam;
}tabSim;

typedef tabSim* TabSim;

TabSim criaTabSim(int tam){
	TabSim t = malloc(sizeof(TabSim));
	t->l = malloc(tam * sizeof(Lista));
	for(int i = 0; i < tam; i++) t->l[i] = criaLista();
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

int insereNaTabSim(TabSim t, char *n, Elemento *val){
	int nHash = funcHash(n, t->tam);
	insereNaLista(t->l[nHash], val);
	return 1;
}

Elemento *buscaNaTabSim(TabSim t, char *n){
	int nHash = funcHash(n, t->tam);
	return (buscaNaLista(t->l[nHash], n));
}

