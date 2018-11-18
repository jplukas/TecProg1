#ifndef LIBGAME_H
#define LIBGAME_H

/* Comeca Includes e defs */
	#include "elemento.h"
	#include "lista.h"
	#include "tabSim.h"
/* Termina Includes e defs */

typedef struct jogo{
	Elemento Aventureiro;
	Elemento lugar_atual;
	TabSim acoes_gerais;
}jogo;

jogo Jogo;

void inicializa_jogo();

unsigned short int itera();
/* Comeca Verbos genericos de objeto */

		

/* Termina Verbos genericos de objeto */

#endif /* LIBGAME_H */