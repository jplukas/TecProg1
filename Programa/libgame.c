#include "libgame.h"
#define TAM_ENTRADA 50
#define TAM_TABSIM 31

char entrada_texto[TAM_ENTRADA];

unsigned short int GAME_OVER;

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
		printf("Não há nenhum(a) %s aqui.\n\n", chave);
		return TRUE;
	}
	if(!getVisivel(objeto) || !getAtivo(objeto) || getTipo(objeto) != OBJ){
		if(getTipo(objeto) != OBJ){
			printf("Você não pode pegar %s, silly!\n\n", chave);
			colocaEmElemento(objeto, lugar, chave);
		}
		else{
			printf("Não há nenhum(a) %s aqui.\n\n", chave);
		}
		return TRUE;
	}
	printf("Você pegou %s.\n", getNome(objeto));
	if(!getConhecido(objeto)){
		printf("Descrição: %s\n\n", getLonga(objeto));
	}
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
	printf("Conteudo de %s:\n\n", getNome(Jogo.lugar_atual));
	Elemento item = itera_elemento(Jogo.lugar_atual);
	while(item && getAtivo(item) && getVisivel(item)){
		printf("Nome: %s\n\n", getNome(item));
		item = itera_elemento(NULL);
	}
	printf("\n");
	return TRUE;
}

unsigned short int listar_inventorio(void* lugar, void* IGNORAR){
	printf("Conteudo de AVENTUREIRO:\n");
	Elemento item = itera_elemento(Jogo.Aventureiro);
	while(item && getAtivo(item) && getVisivel(item)){
		printf("Nome: %s\n\n", getNome(item));
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
		printf("Você deixou o item %s %s em \n", chave, getNome(el));
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
		printf("Vamos, AVENTUREIRO! Uma aventura espera por você!\n\n");
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
	Elemento obj = retiraDeConteudo(Jogo.lugar_atual, "AVENTUREIRO");
	Jogo.lugar_atual = destino;
	colocaEmElemento(obj, Jogo.lugar_atual, "AVENTUREIRO");
	printf("%s\n\n", getLonga(saida));
	return TRUE;
}

unsigned short int descrever_lugar(void* IGNORAR, void* IGNORAR2){
	if(!getVisivel(Jogo.lugar_atual)){
		printf("Não é possível ver nada.\n\n");
		return TRUE;
	}
	printf("%s\n", getNome(Jogo.lugar_atual));
	printf("%s\n", getLonga(Jogo.lugar_atual));
	printf("\n");
	return TRUE;
}

Elemento saida_sul_entrada_caverna;

Elemento sul_caverna;

Elemento portal;

unsigned short int jogar(void* obj, void* IGNORAR2){
	if(!obj) return FALSE;
	char* chave = (char*)obj;
	Elemento objeto = retiraDeConteudo(Jogo.Aventureiro, chave);
	if(!objeto || strcmp(getNome(objeto), "ESPADA")!=0){
		printf("O LAGO não aceita sua oferta!\n\n");
		return colocaEmElemento(objeto, Jogo.Aventureiro, chave);
	}
	printf("O LAGO aceita sua oferta!\n\
Você ouve um som estrondoso vindo do NORTE!\n\n");
	setVisivel(saida_sul_entrada_caverna, FALSE);
	setVisivel(portal, TRUE);
	return colocaEmElemento(objeto, sul_caverna, chave);
}

unsigned short int entrar_portal(void* obj, void* IGNORAR2){
	if(!obj) return FALSE;
	printf("Parabéns, você ganhou o jogo!\n\n");
	GAME_OVER = TRUE;
	return TRUE;
}

void inicializa_jogo(){
	GAME_OVER = FALSE;

	Elemento Lugar_inicial = criaLugar("ENTRADA DA CAVERNA", "Primeiro local do jogo", \
	"Você se encontra em uma caverna escura e fria, e se pergunta se está sozinho.\n\
Não é possível ver ninguém e sons de água corrente se ouvem mais para dentro da caverna.", TRUE, TRUE, FALSE);

	Elemento Aventureiro = criaAventureiro("AVENTUREIRO", "Finn, o Humano",\
	 "Finn é o último humano da terra de OOO. Junto com seu cão mágico Jake, eles\
partirão em busca de incríveis aventuras!");

	sul_caverna = criaLugar("SUL DA CAVERNA", "Interior da caverna ao sul da entrada.", \
	"Você vê que a caverna está ficando mais clara. Há uma espécie de altar iluminado por tochas. No meio do altar há um ancião. Ele parece ciente da sua presença no lugar, e parece estar te esperando. Você pode tentar INTERAGIR.", \
	TRUE, TRUE, FALSE);

	Elemento anciao_sul_caverna = criaNPC("ANCIAO", "...", "Um ancião está em um altar, de olhos abertos e bem fixos em você, porém ele não aparenta ser uma ameaça. Parece que ele já esperava por você. Você pode tentar INTERAGIR.", \
	TRUE, TRUE, FALSE);

	saida_sul_entrada_caverna = criaSaida("SAIDA SUL", "Caminho para para dentro da caverna", \
		"Você avança para dentro da caverna.", TRUE, TRUE, FALSE, sul_caverna);

	Elemento escalibur = criaObj("ESPADA", "Espada mágica do tipo Claymore",\
	"A lendária Escalibur, a Claymore mágica que o Magnífico Rei Arthur \
(que viva para sempre!) tirou da Rocha para se tornar rei da Inglaterra.", TRUE, TRUE, FALSE);

	Elemento floresta = criaLugar("FLORESTA", "FLORESTA", "Você se depara com uma floresta grande e densa. Tão densa que nem a luz do sol consegue atravessá-la.\n\
Você olha ao redor e vê uma espécie de trilha que leva a OESTE.", TRUE, TRUE, FALSE);

	Elemento clareira = criaLugar("CLAREIRA", "CLAREIRA", "Você está em uma clareira na FLORESTA.\n\
Há uma inscrição em pedra com os seguintes dizeres: \"Me dá a ESPADA, que eu cuido do resto!\", e um LAGO.\n\
O LAGO parece pulsar, como se esperasse por algo...\n\
Você também nota, escondido atrás de arbustos, um caminho para o NORTE.", TRUE, TRUE, FALSE);


	Elemento final = criaLugar("MONUMENTO", "????", "Você está em um lugar da FLORESTA onde a luz do sol já\
consegue atravessar as copas das árvores. Você vê uma espécie de MONUMENTO de pedra à sua frente, e ao redor \
dele a FLORESTA se torna muito densa para atravessar.", TRUE, TRUE, FALSE);

	portal = criaObj("PORTAL", "????", "Você vê um PORTAL bem ao lado do MONUMENTO, mas não pode ver \
o que há do outro lado. Você deseja ENTRAR?", TRUE, FALSE, FALSE);

	Elemento clareira_final = criaSaida("NORTE", "???", "Você segue por um caminho muito bem escondido \
por entre as árvores. O caminho é longo, mas você chega ao seu destino.", TRUE, TRUE, FALSE, final);

	Elemento final_clareira = criaSaida("SUL", "Caminho para a CLAREIRA", "Você ruma de volta à CLAREIRA.", \
		TRUE, TRUE, FALSE, clareira);

	Elemento floresta_clareira = criaSaida("OESTE", "Saída em direção à CLAREIRA", \
		"Você sai da FLORESTA em direção à CLAREIRA.", TRUE, TRUE, FALSE, clareira);

	Elemento clareira_floresta = criaSaida("LESTE", "Saída em direção à FLORESTA", \
		"Você sai da CLAREIRA em direção à FLORESTA.", TRUE, TRUE, FALSE, floresta);	

	Elemento en_cav_floresta = criaSaida("SAIDA NORTE", "Saída em direção à FLORESTA", \
		"Você sai da ENTRADA DA CAVERNA em direção à FLORESTA.", TRUE, TRUE, FALSE, floresta);

	Elemento floresta_en_cav = criaSaida("SAIDA SUL", "Saída em direção à ENTRADA DA CAVERNA", \
		"Você avança ao SUL, em direção à ENTRADA DA CAVERNA.", TRUE, TRUE, FALSE, Lugar_inicial);	

	unsigned short int res = 1;

	res = colocaEmElemento(portal, final, "PORTAL");

	res = addSaida(floresta, floresta_clareira, "OESTE");

	res = addSaida(clareira, clareira_floresta, "LESTE");

	res = addSaida(clareira, clareira_final, "NORTE");

	res = addSaida(final, final_clareira, "SUL");	

	Elemento saida_norte_sul_caverna = criaSaida("SAIDA NORTE", "Saída em direção à ENTRADA DA CAVERNA", \
		"Você anda rumo ao norte, para a ENTRADA DA CAVERNA.", TRUE, TRUE, FALSE, Lugar_inicial);
	res = addSaida(sul_caverna, saida_norte_sul_caverna, "NORTE");

	res = addSaida(floresta, floresta_en_cav, "SUL");

	res = addSaida(Lugar_inicial, en_cav_floresta, "NORTE");

	res = addSaida(Lugar_inicial, saida_sul_entrada_caverna, "SUL");

	res = colocaEmElemento(Aventureiro, Lugar_inicial, "AVENTUREIRO");

	res = colocaEmElemento(anciao_sul_caverna, sul_caverna, "ANCIAO");

	res = colocaEmElemento(escalibur, anciao_sul_caverna, "ESPADA");	


	//TabSim acoes = criaTabSim(TAM_TABSIM);

	Jogo.lugar_atual = Lugar_inicial;
	Jogo.Aventureiro = Aventureiro;
 
	res = carregaVerbo(Aventureiro, chorar, "CHORE");

	res = carregaVerbo(clareira, jogar, "JOGUE");

	res = carregaVerbo(portal, entrar_portal, "ENTRE");

	res = carregaVerbo(Aventureiro, pegar, "PEGUE");

	res = carregaVerbo(Aventureiro, mostrar_item_inventorio, "EXAMINE");

	res = carregaVerbo(Aventureiro, listar_inventorio, "LISTE");

	res = carregaVerbo(Aventureiro, largar, "LARGUE");	

	res = carregaVerbo(Lugar_inicial, mostrar_item_lugar, "EXAMINE");

	res = carregaVerbo(Lugar_inicial, descrever_lugar, "DESCREVA");

	res = carregaVerbo(Lugar_inicial, listar_lugar, "LISTE");

	res = carregaVerbo(Lugar_inicial, mover, "MOVA");

	res = carregaVerbo(clareira, mostrar_item_lugar, "EXAMINE");

	res = carregaVerbo(clareira, descrever_lugar, "DESCREVA");

	res = carregaVerbo(clareira, listar_lugar, "LISTE");

	res = carregaVerbo(clareira, mover, "MOVA");

	res = carregaVerbo(final, mostrar_item_lugar, "EXAMINE");

	res = carregaVerbo(final, descrever_lugar, "DESCREVA");

	res = carregaVerbo(final, listar_lugar, "LISTE");

	res = carregaVerbo(final, mover, "MOVA");

	res = carregaVerbo(sul_caverna, descrever_lugar, "DESCREVA");	

	res = carregaVerbo(sul_caverna, mostrar_item_lugar, "EXAMINE");

	res = carregaVerbo(sul_caverna, listar_lugar, "LISTE");

	res = carregaVerbo(sul_caverna, mover, "MOVA");	

	res = carregaVerbo(floresta, mostrar_item_lugar, "EXAMINE");

	res = carregaVerbo(floresta, descrever_lugar, "DESCREVA");

	res = carregaVerbo(floresta, listar_lugar, "LISTE");

	res = carregaVerbo(floresta, mover, "MOVA");	

	res = carregaVerbo(anciao_sul_caverna, interagir_anciao, "INTERAJA");	

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
	if(res) return 0;
	res = executaVerbo(Jogo.Aventureiro, verbo, complemento, NULL);
	if(res) return 0;
	Elemento obj = buscaDeConteudo(Jogo.lugar_atual, complemento);
	if(!obj || !getAtivo(obj) || !getVisivel(obj)){
		printf("Comando inválido!\n\n");
		return 0;
	}
	res = executaVerbo(obj, verbo, complemento, NULL);
	if(!res) printf("Comando inválido!\n");
	printf("\n");
	return GAME_OVER;
}