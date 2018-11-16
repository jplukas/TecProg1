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
//#include "libgame.h"
void entrada(char* a, int t){
	fgets(a, t, stdin);
	fflush(stdin);
	if ((strlen(a) > 0) && (a[strlen (a) - 1] == '\n'))
        a[strlen (a) - 1] = '\0';
}

typedef struct jogo{
	Elemento lugar;
	Elemento Aventureiro;
}jogo;

jogo Jogo;

unsigned short int chorar(void* a, void* b){
	printf("BUAAAA, BUAAAAAA\nESTOU CHORANDO!\n");
	return TRUE;
}

unsigned short int pegar(void* obj, void* IGNORAR){
	Elemento lugar = Jogo.lugar;
	Elemento Aventureiro = Jogo.Aventureiro;
	char* chave = (char*)obj;
	Elemento objeto = retiraDeConteudo(lugar, chave);
	if(!objeto){
		printf("Não há nenhum(a) %s aqui.\n", chave);
		return FALSE;
	}
	printf("Você pegou %s.\n", getNome(objeto));
	printf("Descrição longa: %s\n", getLonga(objeto));
	return colocaEmElemento(objeto, Aventureiro, chave);
}

unsigned short int mostrar_lugar(void* obj, void* IGNORAR){
	Elemento lugar = Jogo.lugar;
	char* chave = (char*)obj;
	Elemento objeto = buscaDeConteudo(lugar, chave);
	if(!objeto){
		printf("Não há nenhum(a) %s aqui.\n", chave);
		return FALSE;
	}
	mostraElemento(objeto);
	return TRUE;
}

unsigned short int mostrar_inventorio(void* obj, void* IGNORAR){
	Elemento lugar = Jogo.Aventureiro;
	char* chave = (char*)obj;
	Elemento objeto = buscaDeConteudo(lugar, chave);
	if(!objeto){
		printf("Não há nenhum(a) %s no seu inventório.\n", chave);
		return FALSE;
	}
	mostraElemento(objeto);
	return TRUE;
}

int main(){

	Elemento escalibur = criaObj("E", "Espada mágica do tipo Claymore",\
		"A lendária Escalibur, a Claymore mágica que o Magnífico Rei Arthur \
(que viva para sempre!) tirou da Rocha para se tornar rei da Inglaterra.", TRUE, TRUE, TRUE);

	Elemento Lugar_inicial = criaLugar("Entrada da caverna", "Primeiro local do jogo", \
	"Você se encontra em uma caverna escura e fria, e se pergunta se está sozinho.\n\
Não é possível ver ninguém e sons de água corrente se ouvem mais para dentro da caverna.", TRUE, TRUE, TRUE);

	Elemento Aventureiro = criaAventureiro("Finn", "Finn, o Humano",\
	 "Finn é o último humano da terra de OOO. Junto com seu cão mágico Jake, eles\
 partirão em busca de incríveis aventuras!");

	colocaEmElemento(Aventureiro, Lugar_inicial, "Aventureiro");

	Jogo.lugar = Lugar_inicial;
	Jogo.Aventureiro = Aventureiro;


	unsigned short int res = carregaVerbo(Aventureiro, chorar, "CHORE");

	res = colocaEmElemento(escalibur, Lugar_inicial, "Espada");	

	res = carregaVerbo(Aventureiro, pegar, "PEGUE");

	res = carregaVerbo(Lugar_inicial, mostrar_lugar, "EXAMINE");

	res = carregaVerbo(Aventureiro, mostrar_inventorio, "EXAMINE");

	unsigned short int (*func)(void*, void*) = NULL;
	/*
	func = buscaVerbo(Lugar_inicial, "EXAMINE");

	res = func("Aventureiro", NULL);

	func = buscaVerbo(Lugar_inicial, "EXAMINE");

	res = func("Espada", NULL);	
	*/
	func = buscaVerbo(Aventureiro, "EXAMINE");

	res = func("Espada", NULL);

	func = buscaVerbo(Aventureiro, "PEGUE");

	res = func("Espada", NULL);

	printf("%s\n", getNome(Aventureiro));

	printf("%s\n", getCurta(Aventureiro));

	printf("%s\n", getLonga(Aventureiro));

	printf("%s\n", getNome(Lugar_inicial));

	printf("%s\n", getCurta(Lugar_inicial));

	printf("%s\n", getLonga(Lugar_inicial));

	printf("%s\n", getNome(escalibur));

	printf("%s\n", getCurta(escalibur));

	printf("%s\n", getLonga(escalibur));

	mostraElemento(escalibur);
	/*
	func = buscaVerbo(Lugar_inicial, "EXAMINE");

	res = func("Aventureiro", NULL);
	func = buscaVerbo(Aventureiro, "EXAMINE");

	res = func("Espada", NULL);	
	*/
	//mostraElemento((void*)Aventureiro);
	//mostraElemento((void*)escalibur);

	return 0;
}
