#ifndef ELEMENTO_H
#define ELEMENTO_H

#define TAM_NOME 80

#ifndef NULL
#define NULL 0
#endif /* NULL */

#ifndef FALSE
#define FALSE 0
#endif /* FALSE */

#ifndef TRUE
#define TRUE 1
#endif /* TRUE */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct{
	char n[TAM_NOME];
}elemento;

typedef elemento * Elemento;

//Funcao que cria e retorna um ponteiro para um elemento.
//Recebe como parametro uma "string" que sera o nome do elemento.

Elemento criaElemento(char n[]){
	Elemento el = malloc(sizeof(Elemento));
	strcpy(el->n, n);
	return el;
}

#endif /* ELEMENTO_H */