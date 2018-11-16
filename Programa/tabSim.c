#include "tabSim.h"

typedef struct tabSim{
	int m;
	ListaFptr* tab;
}tabSim;

int funcHash(int m, char* chave){
	int k = 0;
	int n = strlen(chave);
	for(int i = 0; i <= n; i++)
		k = (PRIME * k + chave[i]) % m;
	return k;
}

TabSim criaTabSim(int m){
	tabSim* t = malloc(sizeof(tabSim));
	t->m = m;
	t->tab = malloc(m * sizeof(ListaFptr));
	for(int i = 0; i < m; i++) t->tab[i] = criaListaFptr();
	return ((TabSim)t);
}

unsigned short int destroiTabSim(TabSim t){
	if(!t) return 0;
	tabSim* tab = (tabSim*)t;
	for(int i = 0; i < tab->m; i++){
		destroiListaFptr(tab->tab[i]);
		tab->tab[i] = NULL;
	}
	free(tab->tab);
	tab->tab = NULL;
	free(t);
	return 1;
}

unsigned short int insereNaTabela(TabSim t, char* chave, unsigned short int (*acao)(void*, void*)){
	tabSim* tab = (tabSim*)t;
	int nHash = funcHash(tab->m, chave);
	return insereListaFptr(tab->tab[nHash], chave, acao);
}

unsigned short int(*buscaNaTabela(TabSim t, char* chave))(void*, void*){
	tabSim* tab = (tabSim*)t;
	int nHash = funcHash(tab->m, chave);
	return buscaListaFptr(tab->tab[nHash], chave);
}

unsigned short int(*retiraDaTabela(TabSim t, char* chave))(void*, void*){
	tabSim* tab = (tabSim*)t;
	int nHash = funcHash(tab->m, chave);
	return retiraListaFptr(tab->tab[nHash], chave);
}

void percorreTabela(TabSim t){
	tabSim* tab = (tabSim*)t;
	for(int i = 0; i < tab->m;i++)
		percorreListaFptr(tab->tab[i]);
}