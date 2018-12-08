
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elemento.h"
#include "lista.h" 
#include "tabSim.h"
#include "coisas.h"

int yyparse();

int main(){

	inicializa_jogo();
	while(yyparse());
	return 0;
}
