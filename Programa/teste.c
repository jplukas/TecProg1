/***************************************************************************************

CODIGO PARA TESTES DAS FUNCOES E ESTRUTURAS DE DADOS DA BIBLIOTECA
(ainda faltam testes para tabelas de simbolos)
((ainda falta fazer as tabelas de simbolos, rs))

***************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elemento.h"
#include "lista.h" 
#include "tabSim.h"
void entrada(char* a, int t){
	fgets(a, t, stdin);
	fflush(stdin);
	if ((strlen(a) > 0) && (a[strlen (a) - 1] == '\n'))
        a[strlen (a) - 1] = '\0';
}

int main(){
	/*
	printf("Digite os nomes dos elementos que você quer incluir na lista:\n\n");
	Lista l = criaLista();
	
	
	char a[TAM_NOME];
	
	//Pega a entrada do usuario e tira o '\n' do final, se houver.
	//Vai aparecer varias vezes no codigo, entao provavelmente sera melhor
	//criar uma funcao especificamente para isso, para reaproveitar codigo
	//e facilitar a leitura.
	entrada(a, TAM_NOME);

	while(!equals(a, "pare")){
		Elemento * e = criaElemento(a);
		insereNaLista(l, e);
		entrada(a, TAM_NOME);
	}
	printf("\n");
	percorreLista(l);
	printf("\n");
	printf("Agora digite o nome de um item para retirar da lista:\n\n");

	entrada(a, TAM_NOME);

	while(!equals(a, "pare")){
		Elemento * el = retiraDaLista(l, buscaNaLista(l, a));
		if(el)printf("O elemento %s foi retirado da lista.\n", el->n);
		else printf("O elemento %s não foi encontrado na lista\n", a);
		printf("\nAgora vejamos como a lista ficou:\n\n");
		percorreLista(l);
		printf("\n");
		entrada(a, TAM_NOME);
	}
	printf("\n");
	printf("A lista será destruída\n\n");
	destroiLista(l);
	percorreLista(l);
	*/
	char a[TAM_NOME];
	Lista l = criaLista(&comp, &mostra);
	entrada(a, TAM_NOME);
	Elemento e;
	while(strcmp(a, "0")){
		Elemento e = criaElemento(a);
		insereNaLista(l, e);
		entrada(a, TAM_NOME);
	}

	percorreLista(l);	

	entrada(a, TAM_NOME);
	while(strcmp(a, "0")){
		e = criaElemento(a);
		retiraDaLista(l, a);
		percorreLista(l);			
		entrada(a, TAM_NOME);
	}

	//destroiTabSim(t);
	return 0;
}
