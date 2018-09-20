/***************************************************************************************

CODIGO PARA TESTES DAS FUNCOES E ESTRUTURAS DE DADOS DA BIBLIOTECA
(ainda faltam testes para tabelas de simbolos)
((ainda falta fazer as tabelas de simbolos, rs))

***************************************************************************************/


#include "lista.h"
main(){
	printf("Digite os nomes dos elementos que você quer incluir na lista:\n\n");
	Lista l = criaLista();
	
	char a[TAM_NOME];
	
	//Pega a entrada do usuario e tira o '\n' do final, se houver.
	//Vai aparecer varias vezes no codigo, entao provavelmente sera melhor
	//criar uma funcao especificamente para isso, para reaproveitar codigo
	//e facilitar a leitura.
	fgets(a, TAM_NOME, stdin);
	fflush(stdin);
	if ((strlen(a) > 0) && (a[strlen (a) - 1] == '\n'))
        a[strlen (a) - 1] = '\0';

	while(!equals(a, "pare")){
		Elemento * e = criaElemento(a);
		insereNaLista(l, e);
		fgets(a, TAM_NOME, stdin);
		if ((strlen(a) > 0) && (a[strlen (a) - 1] == '\n'))
        a[strlen (a) - 1] = '\0';
    	fflush(stdin);
	}
	printf("\n");
	percorreLista(l);
	printf("\n");
	printf("Agora digite o nome de um item para retirar da lista:\n\n");

	fgets(a, TAM_NOME, stdin);
	if ((strlen(a) > 0) && (a[strlen (a) - 1] == '\n'))
        a[strlen (a) - 1] = '\0';
	fflush(stdin);
	while(!equals(a, "pare")){
		Elemento * el = retiraDaLista(l, buscaNaLista(l, a));
		if(el)printf("O elemento %s foi retirado da lista.\n", el->n);
		else printf("O elemento %s não foi encontrado na lista\n", a);
		printf("\nAgora vejamos como a lista ficou:\n\n");
		percorreLista(l);
		printf("\n");
		fgets(a, TAM_NOME, stdin);
		if ((strlen(a) > 0) && (a[strlen (a) - 1] == '\n'))
        a[strlen (a) - 1] = '\0';
    	fflush(stdin);
	}
	printf("\n");
	printf("A lista será destruída\n\n");
	destroiLista(l);
	percorreLista(l);
}