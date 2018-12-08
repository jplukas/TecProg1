#ifndef LIBGAME_H
#define LIBGAME_H

/* Comeca Includes e defs */
	#include "elemento.h"
	#include "lista.h"
	#include "tabSim.h"
/* Termina Includes e defs */

Elemento Aventureiro;
Elemento lugar_atual;
TabSim acoes_gerais;

void inicializa_jogo();

unsigned short int mover(void* direcao, void* IGNORAR2);
unsigned short int listar(void* lugar, void* IGNORAR);
unsigned short int itera();

#endif /* LIBGAME_H */