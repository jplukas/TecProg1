#define TAM_NOME 80
typedef struct{
	char n[TAM_NOME];
}Elemento;

//Funcao que cria e retorna um ponteiro para um elemento.
//Recebe como parametro uma "string" que sera o nome do elemento.
//(precisa trocar essa funcao "strCopy()" pela funcao da biblioteca
//string.h, "strcpy()")
Elemento * criaElemento(char n[]){
	Elemento * el = malloc(sizeof(Elemento*));
	strCopy(n, el->n);
	return el;
}