#include "elemento.h"

/* Comeca typedefs */
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
		//TabSim acoes;

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
/* Termina typedefs */

/* Comeca funcoes */

	int destroiElemento(void* e){
		if(!e) return -1;
		destroiLista(((elemento*)e)->conteudo);
		if(((elemento*)e)->tipo == LUGAR) destroiLista(((elemento*)e)->detalhe.saida);
		else if(((elemento*)e)->tipo != GEN) destroiLista(((elemento*)e)->detalhe.atributos);
		if(((elemento*)e)->animacao){
			free(((elemento*)e)->animacao);
			((elemento*)e)->animacao = NULL;
		}
		destroiElemento(((elemento*)e)->destino);
		free(e);
		e = 0;
		return 1;
	}

	void mostraElemento(void* e){
		if(!e) return;
		printf("Nome: %s\nDescrição curta: %s\n", ((elemento*)e)->nome, ((elemento*)e)->curta);
	}

	//Funcao que cria e retorna um ponteiro para um elemento.
	Elemento criaElemento(char* nome, char* curta, char* longa,\
		short int ativo, short int visivel, short int conhecido){
		if(strlen(nome) >= TAM_NOME){
			printf("Erro! o parâmetro 'nome' é maior que a constante TAM_NOME\nTamanho do parametro: %lu\nTAM_NOME: %d", strlen(nome), TAM_NOME);
			return NULL;
		}
		if(strlen(curta) >= TAM_CURTA){
			printf("Erro! o parâmetro 'curta' é maior que a constante TAM_CURTA\nTamanho do parametro: %lu\nTAM_CURTA: %d", strlen(curta), TAM_CURTA);
			return NULL;
		}
		if(strlen(longa) >= TAM_LONGA){
			printf("Erro! o parâmetro 'longa' é maior que a constante TAM_LONGA\nTamanho do parametro: %lu\nTAM_LONGA: %d", strlen(longa), TAM_LONGA);
			return NULL;
		}

		elemento* el = malloc(sizeof(elemento));
		strcpy(el->nome, nome);
		strcpy(el->curta, curta);
		strcpy(el->longa, longa);
		el->ativo = ativo;
		el->visivel = visivel;
		el->conhecido = conhecido;
		//el->artigo = {"o", "o", "o", "o"};
		el->tipo = GEN;
		el->conteudo = criaLista(destroiElemento, mostraElemento);
		//el->acoes = criaTabSim();
		el->destino = NULL;
		return (Elemento)el;
	}

	Elemento criaObj(char* nome, char* curta, char* longa,\
		short int ativo, short int visivel, short int conhecido){

		Elemento el = criaElemento(nome, curta, longa, ativo, visivel, conhecido);
		((elemento*)el)->tipo = OBJ;
		((elemento*)el)->detalhe.atributos = criaLista(destroiElemento, mostraElemento);
		return el;
	}

	Elemento criaAventureiro(char* nome, char* curta, char* longa){
		Elemento el = criaElemento(nome, curta, longa, TRUE, TRUE, TRUE);
		((elemento*)el)->tipo = AVENTUREIRO;
		((elemento*)el)->detalhe.atributos = criaLista(destroiElemento, mostraElemento);
		return el;
	}

/* Termina funcoes */