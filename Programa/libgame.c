#include "libgame.h"
#define TAM_ENTRADA 50
#define TAM_TABSIM 31

char entrada_texto[TAM_ENTRADA];

unsigned short int chorar(void* IGNORAR, void* IGNORAR2){
	printf("BUAAAA, BUAAAAAA\nESTOU CHORANDO!\n");
	return TRUE;
}



unsigned short int pegar(void* obj, void* IGNORAR){
	Elemento lugar = Jogo.lugar_atual;
	Elemento Aventureiro = Jogo.Aventureiro;
	char* chave = (char*)obj;
	Elemento objeto = retiraDeConteudo(lugar, chave);
	if(!objeto){
		printf("Não há nenhum(a) %s aqui.\n", chave);
		return TRUE;
	}
	if(!getVisivel(objeto) || !getAtivo(objeto) || getTipo(objeto) != OBJ){
		if(getTipo(objeto) != OBJ) printf("Você não pode pegar %s, silly!\n", chave);
		else{
			colocaEmElemento(objeto, lugar, chave);
			printf("Não há nenhum(a) %s aqui.\n", chave);
		}
		return TRUE;
	}
	printf("Você pegou %s.\n", getNome(objeto));
	printf("Descrição: %s\n\n", getLonga(objeto));
	setConhecido(objeto, TRUE);
	return colocaEmElemento(objeto, Aventureiro, chave);
}

unsigned short int mostrar_item_lugar(void* obj, void* IGNORAR){
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
	setConhecido(objeto, TRUE);
	return TRUE;
}

unsigned short int mostrar_item_inventorio(void* obj, void* IGNORAR){
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
	setConhecido(objeto, TRUE);
	return TRUE;
}

unsigned short int listar_lugar(void* lugar, void* IGNORAR){
	if(lugar && strcmp((char*) lugar, "OBJETOS") != 0) return FALSE;
	Elemento item = itera_elemento(Jogo.lugar_atual);
	while(item){
		printf("Nome: %s\n", getNome(item));
		item = itera_elemento(NULL);
	}
	printf("\n");
	return TRUE;
}

unsigned short int listar_inventorio(void* lugar, void* IGNORAR){
	Elemento item = itera_elemento(Jogo.Aventureiro);
	while(item){
		printf("Nome: %s\n", getNome(item));
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

unsigned short int interagir_anciao(void* IGNORAR, void* IGNORAR2){
	static unsigned short int dialogo_aconteceu = FALSE;
	Elemento anciao = buscaDeConteudo(Jogo.lugar_atual, "ANCIAO");
	if(!anciao) return FALSE;
	if(!dialogo_aconteceu){
		dialogo_aconteceu = TRUE;
		printf("Olá, AVENTUREIRO. Eu estive te esperando há um bom tempo.\n\
Você tem uma grande aventura a frente, e grandes perigos para enfrentar. É perigoso ir sozinho, pegue isto!\n");
		Elemento espada = retiraDeConteudo(anciao, "ESPADA");
		if(colocaEmElemento(espada, Jogo.Aventureiro, "ESPADA")) printf("Você recebeu ESPADA %s\n", getNome(espada));
	}
	else{
		printf("Vamos, AVENTUREIRO! Uma aventura espera por você!\n");
	}
	return TRUE;
}

unsigned short int mover(void* direcao, void* IGNORAR2){
	if(!direcao) return FALSE;
	char* chave = (char*)direcao;
	Elemento saida = buscaDeSaidas(Jogo.lugar_atual, chave);
	if(!saida) return FALSE;
	Elemento destino = getDestino(saida);
	if(!destino) return FALSE;
	Jogo.lugar_atual = destino;
	return TRUE;
}

void inicializa_jogo(){
	Elemento Lugar_inicial = criaLugar("ENTRADA DA CAVERNA", "Primeiro local do jogo", \
	"Você se encontra em uma caverna escura e fria, e se pergunta se está sozinho.\n\
Não é possível ver ninguém e sons de água corrente se ouvem mais para dentro da caverna.", TRUE, TRUE, FALSE);

	Elemento Aventureiro = criaAventureiro("FINN", "Finn, o Humano",\
	 "Finn é o último humano da terra de OOO. Junto com seu cão mágico Jake, eles\
partirão em busca de incríveis aventuras!");


	Elemento sul_caverna = criaLugar("SUL DA CAVERNA", "Interior da caverna ao sul da entrada.", \
	"Você avança para dentro da caverna e encontra uma espécie de altar iluminado por tochas. No meio do altar há um ancião. Ele parece ciente da sua presença no lugar, e parece estar te esperando. Você pode tentar INTERAGIR.", \
	TRUE, TRUE, FALSE);

	Elemento anciao_sul_caverna = criaNPC("ANCIAO", "...", "Um ancião está em um altar, de olhos abertos e bem fixos em você, porém ele não aparenta ser uma ameaça. Parece que ele já esperava por você. Você pode tentar INTERAGIR.", \
	TRUE, TRUE, FALSE);

	Elemento saida_sul_entrada_caverna = criaSaida("SAIDA_SUL", "SAIDA_SUL", "SAIDA_SUL", TRUE, TRUE, FALSE, sul_caverna);

	Elemento escalibur = criaObj("ESCALIBUR", "Espada mágica do tipo Claymore",\
	"A lendária Escalibur, a Claymore mágica que o Magnífico Rei Arthur \
(que viva para sempre!) tirou da Rocha para se tornar rei da Inglaterra.", TRUE, TRUE, TRUE);

	unsigned short int res = 1;

	res = addSaida(Lugar_inicial, saida_sul_entrada_caverna, "SUL");

	res = colocaEmElemento(Aventureiro, Lugar_inicial, "AVENTUREIRO");

	res = colocaEmElemento(anciao_sul_caverna, sul_caverna, "ANCIAO");

	res = colocaEmElemento(escalibur, anciao_sul_caverna, "ESPADA");	


	//TabSim acoes = criaTabSim(TAM_TABSIM);



	Jogo.lugar_atual = Lugar_inicial;
	Jogo.Aventureiro = Aventureiro;
 
	res = carregaVerbo(Aventureiro, chorar, "CHORE");

	res = carregaVerbo(Aventureiro, pegar, "PEGUE");

	res = carregaVerbo(Lugar_inicial, mostrar_item_lugar, "EXAMINE");

	res = carregaVerbo(sul_caverna, mostrar_item_lugar, "EXAMINE");

	res = carregaVerbo(Aventureiro, mostrar_item_inventorio, "EXAMINE");

	res = carregaVerbo(Aventureiro, listar_inventorio, "LISTE");

	res = carregaVerbo(Lugar_inicial, listar_lugar, "LISTE");

	res = carregaVerbo(sul_caverna, listar_lugar, "LISTE");

	res = carregaVerbo(Lugar_inicial, mover, "MOVA");	

	res = carregaVerbo(anciao_sul_caverna, interagir_anciao, "INTERAJA");	

	res = carregaVerbo(Aventureiro, largar, "LARGUE");	

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
		setConhecido(Jogo.lugar_atual, TRUE);
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
	if(!res) printf("Comando inválido!\n");
	printf("\n");
	return res;
}