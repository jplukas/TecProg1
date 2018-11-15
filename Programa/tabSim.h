#ifndef TABSIM_H
#define TABSIM_H

#define PRIME 17

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"

typedef struct tabSim * TabSim;

TabSim criaTabSim(int m, int (*destroi)(void*), void (*mostra)(void*));

int destroiTabSim(TabSim t);

int insereNaTabela(TabSim t, char* chave, void* valor);

void* buscaNaTabela(TabSim t, char* chave);

void* retiraDaTabela(TabSim t, char* chave);

void percorreTabela(TabSim t);
#endif /* TABSIM_H */