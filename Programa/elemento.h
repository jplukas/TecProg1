#ifndef ELEMENTO_H
#define ELEMENTO_H

/* Comeca defs e includes */
	#define TAM_NOME 20
	#define TAM_CURTA 80
	#define TAM_LONGA 200
	#define TAM_ARTIGO 5
	#define NUM_ARTIGOS 4

	#ifndef FALSE
	#define FALSE 0
	#endif /* FALSE */

	#ifndef TRUE
	#define TRUE 1
	#endif /* TRUE */


	#include <string.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include "lista.h"
	//#include "tabSimElem.h"
/* Termina defs e includes */


/* Comeca typedefs */
	typedef enum {GEN, OBJ, LUGAR, AVENTUREIRO}Tipo_elem;

	typedef struct elemento * Elemento;
/* Termina typedefs */


/* Comeca prototipos */
	Elemento criaElemento(char* nome, char* curta, char* longa,\
	short int ativo, short int visivel, short int conhecido);

	Elemento criaObj(char* nome, char* curta, char* longa,\
	short int ativo, short int visivel, short int conhecido);

	Elemento criaAventureiro(char* nome, char* curta, char* longa);

	int destroiElemento(void* e);

	void mostraElemento(void* e);
/* Termina prototipos */

#endif /* ELEMENTO_H */