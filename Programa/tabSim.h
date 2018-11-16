#ifndef TABSIM_H
#define TABSIM_H

#define PRIME 17

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista_fptr.h"

typedef struct tabSim * TabSim;

TabSim criaTabSim(int m);

unsigned short int destroiTabSim(TabSim t);

unsigned short int insereNaTabela(TabSim t, char* chave, unsigned short int (*acao)(void*, void*));

unsigned short int(*buscaNaTabela(TabSim t, char* chave))(void*, void*);

unsigned short int(*retiraDaTabela(TabSim t, char* chave))(void*, void*);

void percorreTabela(TabSim t);
#endif /* TABSIM_H */