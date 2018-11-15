#include "tabSim.h"

typedef struct tabSim{
	int m;
	Lista* tab;
}tabSim;

int funcHash(int m, char* chave){
	int k = 0;
	int n = strlen(chave);
	for(int i = 0; i <= n; i++)
		k = (PRIME * k + chave[i]) % m;
	return k;
}

TabSim criaTabSim(int m, int (*destroi)(void*), void (*mostra)(void*)){
	tabSim* t = malloc(sizeof(tabSim));
	t->m = m;
	t->tab = malloc(m * sizeof(Lista));
	for(int i = 0; i < m; i++) t->tab[i] = criaLista(destroi, mostra);
	return ((TabSim)t);
}

int destroiTabSim(TabSim t){
	if(!t) return 0;
	tabSim* tab = (tabSim*)t;
	for(int i = 0; i < tab->m; i++){
		destroiLista(tab->tab[i]);
		tab->tab[i] = NULL;
	}
	free(tab->tab);
	tab->tab = NULL;
	free(t);
	return 1;
}

int insereNaTabela(TabSim t, char* chave, void* valor){
	tabSim* tab = (tabSim*)t;
	int nHash = funcHash(tab->m, chave);
	return insere(tab->tab[nHash], chave, valor);
}

void* buscaNaTabela(TabSim t, char* chave){
	tabSim* tab = (tabSim*)t;
	int nHash = funcHash(tab->m, chave);
	return busca(tab->tab[nHash], chave);
}

void* retiraDaTabela(TabSim t, char* chave){
	tabSim* tab = (tabSim*)t;
	int nHash = funcHash(tab->m, chave);
	return retira(tab->tab[nHash], chave);
}

void percorreTabela(TabSim t){
	tabSim* tab = (tabSim*)t;
	for(int i = 0; i < tab->m;i++)
		percorre(tab->tab[i]);
}