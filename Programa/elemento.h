#ifndef ELEMENTO_H
#define ELEMENTO_H

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

typedef enum Tipo_elem{GEN, OBJ, LUGAR, AVENTUREIRO};

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
	Elemento el = retiraDaLista(lugar->conteudo);
}

int comp(char* chave, Elemento el){
	return strcmp(chave, el->nome);
}

void mostra(Elemento el){
	printf("%s\n", el->nome);
}

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
	elem * destino;
	short int aberta;

}elemento;

typedef elemento * Elemento;

//Funcao que cria e retorna um ponteiro para um elemento.
//Recebe como parametro uma "string" que sera o nome do elemento.

Elemento criaElemento(char nome[], char curta[], char longa[],\
	short int ativo, short int visivel, short int conhecido, char artigo[][]){
	Elemento el = malloc(sizeof(Elemento));
	strcpy(el->nome, nome);
	strcpy(el->curta, curta);
	strcpy(el->longa, longa);
	el->ativo = ativo;
	el->visivel = visivel;
	el->conhecido = conhecido;
	el->artigo = artigo;
	el->tipo = GEN;
	el->conteudo = criaLista(comp, mostra);
	el->acoes = criaTabSim(NULL, NULL);
	return el;
}

Elemento criaObj(char nome[], char curta[], char longa[],\
	short int ativo, short int visivel, short int conhecido, char artigo[][]){

	Elemento el = criaElemento(nome, curta, longa, ativo, visivel, conhecido, artigo);
	el->tipo = OBJ;
	el->detalhe.atributos = criaLista(comp, mostra);
}

#endif /* ELEMENTO_H */