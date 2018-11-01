#ifndef ELEMENTO_H
#define ELEMENTO_H

/* Comeca defs e includes */
	#define TAM_NOME 20
	#define TAM_CURTA 80
	#define TAM_LONGA 200
	#define TAM_ARTIGO 5
	#define NUM_ARTIGOS 4

	#ifndef NULL
	#define NULL 0
	#endif /* NULL */

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

typedef enum {GEN, OBJ, LUGAR, AVENTUREIRO}Tipo_elem;

typedef union{
	int i;
	double d;
	char c;
	char str[TAM_CURTA];
	void * gen;
}Val;

typedef	struct{
	char nome_attr[TAM_NOME];
	Val val;
}attr;

typedef attr * Attr;

typedef struct elem{
	/* Nome do elemento */
	char nome[TAM_NOME];

	/* Descricao curta */
	char curta[TAM_CURTA];

	/* Descricao longa */
	char longa[TAM_LONGA];

	/* Flags */
	short int ativo;
	short int visivel;
	short int conhecido;

	/* Conteudo do elemento [lista] */
	Lista conteudo;

	/* Acoes ou verbos para o elemento [tabela de hash] */
	TabSim acoes;

	/* A DEFINIR */
	void * animacao;

	/* Artigos para o elemento (a, o, um, da, do, dum...) */
	char artigo[NUM_ARTIGOS][TAM_ARTIGO];

	/* Tipo do elemento (Objeto, lugar, aventureiro, saida...) */
	Tipo_elem tipo;

	/* Atributos de objeto ou lugar ("subclasses" de elemento) */
	union{
		/* Atributo de lugar */
		Lista saida;

		/* Atributo de objeto */
		Lista atributos;
	}detalhe;

	/* Propriedades especificas de lugar */
	/* (NAO USAR SE NAO FOR LUGAR) */
	struct elem * destino;
	short int aberta;

}elemento;

typedef elemento * Elemento;

int comp(char* chave, Elo e){
	return strcmp(chave, e->chave.str);
}

void mostra(Elo e){
	printf("%s: %s\n", e->chave.str, ((Elemento)e->val)->nome);
}

Elo insere(Elemento el, char* chave){
	Elo e = malloc(sizeof(elo) + sizeof(elemento));
	e->val = el;
	strcpy(e->chave.str, chave);
	return e;
}


//Funcao que cria e retorna um ponteiro para um elemento.
//Recebe como parametro uma "string" que sera o nome do elemento.

Elemento criaElemento(char* nome, char* curta, char* longa,\
	short int ativo, short int visivel, short int conhecido){
	Elemento el = malloc(sizeof(elemento));
	/*
	el->nome = malloc(TAM_NOME * sizeof(char));
	el->curta = malloc(TAM_CURTA * sizeof(char));
	el->longa = malloc(TAM_LONGA * sizeof(char));
	*/
	strcpy(el->nome, nome);
	strcpy(el->curta, curta);
	strcpy(el->longa, longa);
	el->ativo = ativo;
	el->visivel = visivel;
	el->conhecido = conhecido;
	//el->artigo = {"o", "o", "o", "o"};
	el->tipo = GEN;
	el->conteudo = criaLista(comp, mostra, insere);
	el->acoes = criaTabSim(100, comp, mostra, insere);
	return el;
}

Elemento criaObj(char* nome, char* curta, char* longa,\
	short int ativo, short int visivel, short int conhecido){

	Elemento el = criaElemento(nome, curta, longa, ativo, visivel, conhecido);
	el->tipo = OBJ;
	el->detalhe.atributos = criaLista(comp, mostra, insere);
}

Elemento criaAventureiro(char* nome, char* curta, char* longa){
	Elemento el = criaElemento(nome, curta, longa, TRUE, TRUE, TRUE);
	el->tipo = AVENTUREIRO;
	el->detalhe.atributos = criaLista(comp, mostra, insere);
}

#endif /* ELEMENTO_H */