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
}

int main(){

	Elemento Lugar_inicial = criaLugar("Entrada da caverna", "Primeiro local do jogo", \
	"Você se encontra em uma caverna escura e fria, e se pergunta se está sozinho.\n\
Não é possível ver ninguém e sons de água corrente se ouvem mais para dentro da caverna.", TRUE, TRUE, TRUE);

	Elemento Aventureiro = criaAventureiro("Finn", "Finn, o Humano",\
	 "Finn é o último humano da terra de OOO. Junto com seu cão mágico Jake, eles\
 partirão em busca de incríveis aventuras!");

	colocaEmElemento(Aventureiro, Lugar_inicial, "Aventureiro");

	Jogo = {Lugar_inicial, Aventureiro};

	Elemento escalibur = criaObj("Escalibur", "Espada mágica do tipo Claymore",\
		"A lendária Escalibur, a Claymore mágica que o Magnífico Rei Arthur \
(que viva para sempre!) tirou da Rocha para se tornar rei da Inglaterra.", TRUE, TRUE, TRUE);

	colocaEmElemento(escalibur, Aventureiro, "Espada");

	unsigned short int res = carregaVerbo(Aventureiro, chorar, "CHORE");

	unsigned short int (*func)(void*, void*) = buscaVerbo(Aventureiro, "CHORE");


	unsigned short int a = TRUE;

	while(a){
		printf("%s\n", getLonga(Jogo.lugar));
		a = FALSE;
	}

	res = func(NULL, NULL);
	//mostraElemento((void*)Aventureiro);
	//mostraElemento((void*)escalibur);

	return 0;
}
