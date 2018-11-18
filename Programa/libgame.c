#include "libgame.h"
#define TAM_ENTRADA 50
#define TAM_TABSIM 31

char entrada_texto[TAM_ENTRADA];

unsigned short int chorar(void* IGNORAR, void* IGNORAR2){
	printf("BUAAAA, BUAAAAAA\nESTOU CHORANDO!\n\n");
	return TRUE;
}

unsigned short int pegar(void* obj, void* IGNORAR){
	Elemento lugar = Jogo.lugar_atual;
	Elemento Aventureiro = Jogo.Aventureiro;
	char* chave = (char*)obj;
	Elemento objeto = retiraDeConteudo(lugar, chave);
	if(!objeto){
		printf("Não há nenhum(a) %s aqui.\n\n", chave);
		return TRUE;
	}
	if(!getVisivel(objeto) || !getAtivo(objeto) || getTipo(objeto) != OBJ){
		if(getTipo(objeto) != OBJ) printf("Você não pode pegar %s, silly!\n", chave);
		else{
			colocaEmElemento(objeto, lugar, chave);
			printf("Não há nenhum(a) %s aqui.\n\n", chave);
		}
		return TRUE;
	}
	printf("Você pegou %s.\n\n", getNome(objeto));
	return colocaEmElemento(objeto, Aventureiro, chave);
}

unsigned short int mostrar_lugar(void* obj, void* IGNORAR){
	Elemento lugar = Jogo.lugar_atual;
	char* chave = (char*)obj;
	Elemento objeto = buscaDeConteudo(lugar, chave);
	if(!objeto || !getVisivel(objeto) || !getAtivo(objeto)){
		printf("Não há nenhum(a) %s aqui.\n\n", chave);
		return FALSE;
	}
	printf("Há um(a) %s aqui!\n", chave);
	mostraElemento(objeto);
	printf("\n");
	return TRUE;
}

unsigned short int mostrar_inventorio(void* obj, void* IGNORAR){
	if(!obj) return FALSE;
	Elemento lugar = Jogo.Aventureiro;
	char* chave = (char*)obj;
	Elemento objeto = buscaDeConteudo(lugar, chave);
	if(!objeto){
		printf("Não há nenhum(a) %s no seu inventório.\n\n", chave);
		return TRUE;
	}
	printf("Há um(a) %s no seu inventório!\n", chave);
	mostraElemento(objeto);
	printf("\n");
	return TRUE;
}

unsigned short int listar_lugar(void* lugar, void* IGNORAR){
	if(lugar && strcmp((char*) lugar, "OBJETOS") != 0) return FALSE;
	Elemento item = itera_elemento(Jogo.lugar_atual);
	while(item){
		printf("Nome: %s\n", getNome(item));
		printf("Descrição: %s\n\n", getLonga(item));
		item = itera_elemento(NULL);
	}
	printf("\n");
	return TRUE;
}

unsigned short int listar_inventorio(void* lugar, void* IGNORAR){
	Elemento item = itera_elemento(Jogo.Aventureiro);
	while(item){
		printf("Nome: %s\n", getNome(item));
		printf("Descrição: %s\n\n", getLonga(item));
		item = itera_elemento(NULL);
	}
	printf("\n");
	return TRUE;
}

unsigned short int largar(void* obj, void* IGNORAR){
	if(!obj) return FALSE;
	char* chave = (char*)obj;
	Elemento el = retiraDeConteudo(Jogo.Aventureiro, chave);
	if(!el){
		printf("Não há nenhum(a) %s no seu inventório.\n\n", chave);
		return TRUE;
	}
	if(colocaEmElemento(el, Jogo.lugar_atual, chave)){
		printf("Você deixou o item %s %s em ", chave, getNome(el));
		printf("%s.\n", getNome(Jogo.lugar_atual));
		return TRUE;
	}
	else{
		colocaEmElemento(el, Jogo.Aventureiro, chave);
		printf("Você não conseguiu largar %s.\n", chave);
		return TRUE;
	}
}

void inicializa_jogo(){
	Elemento Lugar_inicial = criaLugar("Entrada da caverna", "Primeiro local do jogo", \
	"Você se encontra em uma caverna escura e fria, e se pergunta se está sozinho.\n\
Não é possível ver ninguém e sons de água corrente se ouvem mais para dentro da caverna.", TRUE, TRUE, FALSE);

	Elemento Aventureiro = criaAventureiro("Finn", "Finn, o Humano",\
	 "Finn é o último humano da terra de OOO. Junto com seu cão mágico Jake, eles\
partirão em busca de incríveis aventuras!");

	//TabSim acoes = criaTabSim(TAM_TABSIM);

	unsigned short int res = 1;

	res = colocaEmElemento(Aventureiro, Lugar_inicial, "AVENTUREIRO");

	Elemento escalibur = criaObj("Escalibur", "Espada mágica do tipo Claymore",\
	"A lendária Escalibur, a Claymore mágica que o Magnífico Rei Arthur \
(que viva para sempre!) tirou da Rocha para se tornar rei da Inglaterra.", TRUE, TRUE, TRUE);

	Jogo.lugar_atual = Lugar_inicial;
	Jogo.Aventureiro = Aventureiro;
 
	printf("Nome do lugar: %s", getNome(Jogo.lugar_atual));

	res = carregaVerbo(Aventureiro, chorar, "CHORE");

	res = carregaVerbo(Aventureiro, pegar, "PEGUE");

	res = carregaVerbo(Lugar_inicial, mostrar_lugar, "EXAMINE");

	res = carregaVerbo(Aventureiro, mostrar_inventorio, "EXAMINE");

	res = carregaVerbo(Lugar_inicial, listar_lugar, "LISTAR");

	res = carregaVerbo(Aventureiro, listar_inventorio, "LISTAR");

	res = carregaVerbo(Aventureiro, largar, "LARGAR");

	res = colocaEmElemento(escalibur, Lugar_inicial, "ESPADA");	

	printf("\n");
}

void entrada(char* a, int t){
	fgets(a, t, stdin);
	fflush(stdin);
	if ((strlen(a) > 0) && (a[strlen (a) - 1] == '\n'))
        a[strlen (a) - 1] = '\0';
}

unsigned short int itera(){
	char* verbo = NULL;
	char* complemento = NULL;
	if(!getConhecido(Jogo.lugar_atual)){
		printf("%s\n", getLonga(Jogo.lugar_atual));
		setConhecido(Jogo.lugar_atual, 1);
		printf("\n");
		listar_lugar(NULL, NULL);
	}
	entrada(entrada_texto, TAM_ENTRADA);
	verbo = strtok(entrada_texto, " ");
	complemento = strtok(NULL, " ");
	unsigned short int res = 1;
	res = executaVerbo(Jogo.lugar_atual, verbo, complemento, NULL);
	if(res) return 1;
	res = executaVerbo(Jogo.Aventureiro, verbo, complemento, NULL);
	if(res) return 1;
	Elemento obj = buscaDeConteudo(Jogo.lugar_atual, complemento);
	if(!obj){
		printf("Comando inválido!\n");
		return 0;
	}
	res = executaVerbo(obj, verbo, complemento, NULL);
	printf("\n");
	return res;
}