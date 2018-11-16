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
		unsigned short int ativo;
		unsigned short int visivel;
		unsigned short int conhecido;

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
			Lista saidas;

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
	int destroiElemento(void* this){
		if(!this) return -1;
		elemento* e = (elemento*) this;
		destroiLista(e->conteudo);
		if(e->tipo == LUGAR) destroiLista(e->detalhe.saidas);
		else if(e->tipo != GEN) destroiLista(e->detalhe.atributos);
		if(e->animacao){
			free(e->animacao);
			e->animacao = NULL;
		}
		destroiElemento(((elemento*)e)->destino);
		free(this);
		this = 0;
		return TRUE;
	}

	void mostraElemento(void* this){
		if(!this) return;
		elemento* e = (elemento*) this;
		printf("Nome: %s\nDescrição curta: %s\n", e->nome, e->curta);
		printf("Conteudo de %s:\n", e->nome);
		percorre(e->conteudo);
		printf("\n");
	}

	//Funcao que cria e retorna um ponteiro para um elemento.
	Elemento criaElemento(char* nome, char* curta, char* longa,\
	unsigned short int ativo, unsigned short int visivel, unsigned short int conhecido){
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
		el->acoes = criaTabSim(TAM_TABSIM);
		el->destino = NULL;
		return (Elemento)el;
	}

	Elemento criaObj(char* nome, char* curta, char* longa,\
	unsigned short int ativo, unsigned short int visivel, unsigned short int conhecido){

		elemento* el = (elemento*)criaElemento(nome, curta, longa, ativo, visivel, conhecido);
		el->tipo = OBJ;
		el->detalhe.atributos = criaLista(destroiElemento, mostraElemento);
		return (Elemento)el;
	}

	Elemento criaLugar(char* nome, char* curta, char* longa,\
	unsigned short int ativo, unsigned short int visivel, unsigned short int conhecido){

		elemento* el = (elemento*)criaElemento(nome, curta, longa, ativo, visivel, conhecido);
		el->tipo = LUGAR;
		el->detalhe.saidas = criaLista(destroiElemento, mostraElemento);
		return (Elemento)el;
	}

	Elemento criaAventureiro(char* nome, char* curta, char* longa){
		elemento* el = (elemento*)criaElemento(nome, curta, longa, TRUE, TRUE, TRUE);
		el->tipo = AVENTUREIRO;
		el->detalhe.atributos = criaLista(destroiElemento, mostraElemento);
		return (Elemento)el;
	}

	char* getNome(Elemento this){
		if(!this) return NULL;
		static char nome[TAM_NOME];
		strcpy(nome, ((elemento*)this)->nome);
		return nome;
	}

	char* getCurta(Elemento this){
		if(!this) return NULL;
		static char curta[TAM_CURTA];
		strcpy(curta, ((elemento*)this)->curta);
		return curta;
	}

	char* getLonga(Elemento this){
		if(!this) return NULL;
		static char longa[TAM_LONGA];
		strcpy(longa, ((elemento*)this)->longa);
		return longa;
	}

	unsigned short int getAtivo(Elemento this){
		if(!this) return FALSE;
		return ((elemento*)this)->ativo;
	}

	void setAtivo(Elemento this, unsigned short int ativo){
		if(!this) return;
		((elemento*)this)->ativo = ativo;
	}

	unsigned short int getVisivel(Elemento this){
		if(!this) return FALSE;
		return ((elemento*)this)->visivel;
	}

	void setVisivel(Elemento this, unsigned short int visivel){
		if(!this) return;
		((elemento*)this)->visivel = visivel;
	}

	unsigned short int getConhecido(Elemento this){
		if(!this) return FALSE;
		return ((elemento*)this)->conhecido;
	}

	void setConhecido(Elemento this, unsigned short int conhecido){
		if(!this) return;
		((elemento*)this)->conhecido = conhecido;
	}

	Elemento buscaDeConteudo(Elemento this, char* chave){
		if(!this || !chave) return NULL;
		return ((Elemento)busca(((elemento*)this)->conteudo, chave));
	}

	Elemento retiraDeConteudo(Elemento this, char* chave){
		if(!this || !chave) return NULL;
		return ((Elemento)retira(((elemento*)this)->conteudo, chave));
	}

	unsigned short int colocaEmElemento(Elemento obj, Elemento destino, char* chave){
		if(!obj || !destino) return FALSE;
		insere(((elemento*)destino)->conteudo, chave, ((void*)obj));
		return TRUE;
	}

	unsigned short int carregaVerbo(Elemento this, unsigned short int (*verbo)(void*, void*), char* chave){
		if(!this || !verbo || !chave) return FALSE;
		elemento* e = (elemento*) this;
		return insereNaTabela(e->acoes, chave, verbo);
	}

	unsigned short int (*buscaVerbo(Elemento this, char* chave))(void*, void*){
		if(!this || !chave) return NULL;
		return buscaNaTabela(((elemento*)this)->acoes, chave);
	}

/* Termina funcoes */