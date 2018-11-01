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
#include "libgame.h"
void entrada(char* a, int t){
	fgets(a, t, stdin);
	fflush(stdin);
	if ((strlen(a) > 0) && (a[strlen (a) - 1] == '\n'))
        a[strlen (a) - 1] = '\0';
}

int main(){
	Aventureiro = criaAventureiro("Finn", "Finn, o Humano",\
	 "Finn é o último humano da terra de OOO. Junto com seu cão mágico Jake, eles\
 partirão em busca de incríveis aventuras!");

	Elemento escalibur = criaObj("Escalibur", "Espada mágica do tipo Claymore",\
		"A lendária Escalibur, a Claymore mágica que o Magnífico Rei Arthur \
(que viva para sempre!) tirou da Rocha para se tornar rei da Inglaterra.", TRUE, TRUE, TRUE);

	insereNaLista(Aventureiro->conteudo, escalibur, "Espada");

	percorreLista(Aventureiro->conteudo);

	Elemento e = buscaNaLista(Aventureiro->conteudo, "Espada");


	printf("obj: %p\nrec: %p\n", (void*)escalibur, (void*)e);
	//printf("%s\n", e->curta);
	//printf("%s\n", e->longa);
	//printf("%p\n", (void*)e);
	//printf("%p\n", (void*)escalibur);
	//examina(e, NULL);

	/*
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
	*/
	return 0;
}
