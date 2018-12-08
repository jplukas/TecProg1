/* Calculadora infixa */

%{
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
  Elemento  direc;
}

%token <elem> OBJ

/* DESC representa uma palavra desconhecida */
%token <str> DESC
%token  NORTE SUL LESTE OESTE CIMA BAIXO EOL FIM INVENT

%type <direc> dir
%type <verbo> VERBO

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
			| INDEF OBJ {
					unsigned short int (*v)(void*, void*) = buscaVerbo($2, $1);
					if(!v) puts("COMANDO INVALIDO");
					else{
						v($2, NULL);
					}
				} eol
			| DESC { puts("COMANDO INVALIDO");}
			| error eol;
;

cmd: VERBO {
			 /* Intransitivo */
  	 	     $1(NULL, NULL);
		   } eol
   | VERBO OBJ {
			   /* Transitivo direto */
			   $1($2, NULL);
			 } eol 
   | VERBO OBJ OBJ {
                 /* Bitransitivo */
			     $1($2, $3);
			   } eol
   | VERBO DESC {
			     printf("%s??\n", $2);
			 } eol 
   | VERBO OBJ DESC {
			   printf("não sei o que é isso: %s\n",  $3);
			   } eol 
   | VERBO DESC DESC {
			     printf("Pare de jogar e vá descansar um pouco\n"
						"Fazer isso com %s e %s, que coisa\n", $2,$3
						);
			   } eol 
;

dir: NORTE	{$$=$1;}
	 | SUL		{$$=$1;}
	 | LESTE	{$$=$1;}
	 | OESTE	{$$=$1;}
	 | CIMA		{$$=$1;}
	 | BAIXO	{$$=$1;}
;

eol: EOL {return 1;}
%%

int yyerror(char *s) {
  puts("Não entendi...");
  return 0;
}
