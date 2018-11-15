#ifndef LIBGAME_H
#define LIBGAME_H

/* Comeca Includes e defs */
	#include "elemento.h"
	#include "lista.h"
	#include "tabSim.h"
/* Termina Includes e defs */

Elemento Aventureiro;

/* Comeca Verbos genericos de objeto */

	int examina(Elemento el, void* i){
		if(!el) return 0;
		if(!el->longa) return 0;
		printf("%s\n", el->longa);
		return 1;
	}

	int pegar(Elemento lugar, char * chave){
		if(!lugar) return 0;
		if(!lugar->conteudo) return 0;
		if(!chave) return 0;
		Elemento el = retiraDaLista(lugar->conteudo, chave);
		insereNaLista(Aventureiro->conteudo, el, chave);
		return 1;
	}

	int largar(Elemento lugar, char * chave){
		if(!lugar) return 0;
		if(!lugar->conteudo) return 0;
		if(!chave) return 0;
		Elemento el = retiraDaLista(Aventureiro->conteudo, chave);
		insereNaLista(lugar->conteudo, el, chave);
		return 1;
	}	

/* Termina Verbos genericos de objeto */

#endif /* LIBGAME_H */