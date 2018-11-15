#ifndef ELEMENTO_H
#define ELEMENTO_H

/* Comeca defs e includes */
	#define TAM_NOME 20
	#define TAM_CURTA 80
	#define TAM_LONGA 200
	#define TAM_ARTIGO 5
	#define NUM_ARTIGOS 4
	#define TAM_TABSIM 31

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
	#include "tabSim.h"
/* Termina defs e includes */


/* Comeca typedefs */
	typedef enum {GEN, OBJ, LUGAR, AVENTUREIRO}Tipo_elem;

	typedef struct elemento * Elemento;
/* Termina typedefs */


/* Comeca prototipos */
	int destroiElemento(void* e);

	void mostraElemento(void* e);

	Elemento criaElemento(char* nome, char* curta, char* longa,\
	unsigned short int ativo, unsigned short int visivel, unsigned short int conhecido);

	Elemento criaObj(char* nome, char* curta, char* longa,\
	unsigned short int ativo, unsigned short int visivel, unsigned short int conhecido);

	Elemento criaLugar(char* nome, char* curta, char* longa,\
	unsigned short int ativo, unsigned short int visivel, unsigned short int conhecido);

	Elemento criaAventureiro(char* nome, char* curta, char* longa);

	char* getNome(Elemento this);

	char* getCurta(Elemento this);

	char* getLonga(Elemento this);

	unsigned short int getAtivo(Elemento this);

	void setAtivo(Elemento this, unsigned short int ativo);

	unsigned short int getVisivel(Elemento this);

	void setVisivel(Elemento this, unsigned short int visivel);

	unsigned short int getConhecido(Elemento this);

	void setConhecido(Elemento this, unsigned short int conhecido);

	Elemento buscaDeConteudo(Elemento this, char* chave);

	Elemento retiraDeConteudo(Elemento this, char* chave);

	unsigned short int colocaEmElemento(Elemento obj, Elemento destino, char* chave);

	unsigned short int carregaVerbo(Elemento this, int (*verbo)(void*, void*), char* chave);

	unsigned short int executaVerbo(Elemento this, char* chave);
/* Termina prototipos */

#endif /* ELEMENTO_H */