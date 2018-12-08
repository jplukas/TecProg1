/* Calculadora infixa */

%{
#include "elemento.h"
#include <string.h>
#include <stdio.h>
#include "tabSim.h"
#include "coisas.h"
  
int yylex();
int yyerror(char *);


%}

/* Declaracoes */
%union {
  	Elemento elem;
	unsigned short int (*verbo)(void*, void*);
  	char *str;
}

%token <elem> OBJETO
/* DESC representa uma palavra desconhecida */
%token <str> DESC INDEF
%token <str> NORTE SUL LESTE OESTE CIMA BAIXO EOL FIM INVENT

%type <str> dir
%token <verbo> VERBO
%type <elem> obj

%defines

%%
/* Gramatica */


input:	EOL { printf("Zzzz...\n"); }
			| cmd
			| dir {
				/* movimentação  */
				mover($1, NULL);
			 	} eol
			| INVENT {
				/* listagem do inventário */
				listar(Aventureiro, NULL);
				} eol
			| FIM  { return 0;}
			| INDEF OBJETO {
					$1 = strtok($1, " ");
					unsigned short int (*v)(void*, void*) = buscaVerbo($2, $1);
					if(!v) puts("COMANDO INVALIDO\n");
					else{
						v($2, NULL);
					}
				} eol
			| DESC { puts("COMANDO INVALIDO\n");}
			| error eol;
;

cmd: VERBO {
			 /* Intransitivo */
  	 	     $1(NULL, NULL);
		   } eol
   | VERBO obj {
			   /* Transitivo direto */
			   $1($2, NULL);
			 } eol 
   | VERBO obj obj {
                 /* Bitransitivo */
			     $1($2, $3);
			   } eol
   | VERBO DESC {
			     printf("%s??\n", $2);
			 } eol 
   | VERBO obj DESC {
			   printf("não sei o que é isso: %s\n",  $3);
			   } eol 
   | VERBO DESC DESC {
			     printf("Pare de jogar e vá descansar um pouco\n"
						"Fazer isso com %s e %s, que coisa\n", $2,$3
						);
			   } eol 
;

obj: OBJETO {$$=$1;}

dir: NORTE	{$$="NORTE";}
	 | SUL		{$$="SUL";}
	 | LESTE	{$$="LESTE";}
	 | OESTE	{$$="OESTE";}
;

eol: EOL {return 1;}
%%

int yyerror(char *s) {
  puts("Não entendi...");
  return 0;
}
