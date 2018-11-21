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

int main(){

	inicializa_jogo();

	Elemento Aventureiro = Jogo.Aventureiro;
	Elemento lugar_atual = Jogo.lugar_atual;

	unsigned short int res = 0; 
	while(!res){
		res = itera();
	}
	return 0;
}
