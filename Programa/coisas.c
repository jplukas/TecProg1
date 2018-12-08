#include "coisas.h"
#define TAM_ENTRADA 50
#define TAM_TABSIM 31

/* Variaveis globais */
static unsigned short int GAME_OVER = FALSE;

Elemento Aventureiro = NULL;
Elemento lugar_atual = NULL;
TabSim acoes_gerais = NULL;

Elemento saida_sul_entrada_caverna = NULL;
Elemento sul_caverna = NULL;
Elemento portal = NULL;

unsigned short int chorar(void* IGNORAR, void* IGNORAR2){
	printf("BUAAAA, BUAAAAAA\nESTOU CHORANDO!\n");
	return TRUE;
}

unsigned short int pegarObj(void* obj, void* lugar){
	Elemento objeto = retiraDeConteudo(lugar_atual, getNome(obj));
	if(!getVisivel(objeto)){
		printf("Não há nenhum(a) %s aqui.\n\n", getNome(obj));
		return TRUE;
	}
	if(getTipo(objeto) != OBJ){
		printf("Você não pode pegar %s, silly!\n\n", getNome(obj));
		colocaEmElemento(objeto, lugar, getNome(obj));
		return TRUE;
	}
	printf("Você pegou %s.\n", getNome(objeto));
	if(!getConhecido(objeto)){
		printf("Descrição: %s\n\n", getLonga(objeto));
	}
	setConhecido(objeto, TRUE);
	return colocaEmElemento(objeto, Aventureiro, getNome(objeto));
}

unsigned short int mostrarItem(void* objeto, void* lugar){
	if(!getVisivel(objeto)){
		printf("Não há nenhum(a) %s.\n\n", getNome(objeto));
		return FALSE;
	}
	mostraElemento(objeto);
	printf("\n");
	setConhecido(objeto, TRUE);
	return TRUE;
}

unsigned short int listar(void* lugar, void* IGNORAR){
	printf("Conteudo de %s:\n\n", getNome(lugar));
	Elemento item = itera_elemento(lugar);
	while(item && getAtivo(item) && getVisivel(item)){
		printf("Nome: %s\n\n", getNome(item));
		item = itera_elemento(NULL);
	}
	printf("\n");
	return TRUE;
}

unsigned short int largar(void* obj, void* lugar){
	Elemento el = retiraDeConteudo(Aventureiro, getNome(obj));
	if(!el){
		printf("Não há nenhum(a) %s no seu inventório.\n\n", getNome(obj));
		return TRUE;
	}
	if(colocaEmElemento(el, lugar, getNome(obj))){
		printf("Você deixou o item %s em %s\n", getNome(obj), getNome(lugar));
		return TRUE;
	}
	else{
		colocaEmElemento(el, Aventureiro, getNome(el));
		printf("Você não conseguiu largar %s.\n", getNome(el));
		return TRUE;
	}
}

unsigned short int interagirComAnciao(void* IGNORAR, void* IGNORAR2){
	static unsigned short int dialogo_aconteceu = FALSE;
	Elemento anciao = buscaDeConteudo(lugar_atual, "ANCIAO");
	if(!anciao) return FALSE;
	if(!dialogo_aconteceu){
		dialogo_aconteceu = TRUE;
		printf("Olá, AVENTUREIRO. Eu estive te esperando há um bom tempo.\n\
Você tem uma grande aventura a frente, e grandes perigos para enfrentar. É perigoso ir sozinho, pegue isto!\n");
		Elemento espada = retiraDeConteudo(anciao, "ESPADA");
		if(colocaEmElemento(espada, Aventureiro, "ESPADA")) printf("Você recebeu ESPADA %s\n", getNome(espada));
	}
	else{
		printf("Vamos, AVENTUREIRO! Uma aventura espera por você!\n\n");
	}
	return TRUE;
}

unsigned short int mover(void* direcao, void* IGNORAR2){
	if(!direcao) return FALSE;
	char* chave = (char*)direcao;
	Elemento saida = buscaDeSaidas(lugar_atual, chave);
	if(!saida || !getVisivel(saida)){
		printf("Não há caminho para %s.\n", chave);
		return TRUE;
	}
	if(!getAberta(saida)){
		printf("O caminho para %s está bloqueado!.\n", chave);
		return TRUE;
	}
	Elemento destino = getDestino(saida);
	if(!destino) return FALSE;
	Elemento obj = retiraDeConteudo(lugar_atual, "AVENTUREIRO");
	lugar_atual = destino;
	colocaEmElemento(obj, lugar_atual, "AVENTUREIRO");
	printf("%s\n\n", getLonga(saida));
	return TRUE;
}

unsigned short int descreverLugar(void* IGNORAR, void* IGNORAR2){
	if(!getVisivel(lugar_atual)){
		printf("Não é possível ver nada.\n\n");
		return TRUE;
	}
	printf("%s\n", getNome(lugar_atual));
	printf("%s\n", getLonga(lugar_atual));
	printf("\n");
	return TRUE;
}

unsigned short int jogar(void* obj, void* IGNORAR2){
	Elemento objeto = retiraDeConteudo(Aventureiro, getNome(obj));
	if(!objeto || strcmp(getNome(objeto), "ESPADA")!=0){
		printf("O LAGO não aceita sua oferta!\n\n");
		return colocaEmElemento(objeto, Aventureiro, getNome(obj));
	}
	printf("O LAGO aceita sua oferta!\n\
Você ouve um som estrondoso vindo do NORTE!\n\n");
	setAberta(saida_sul_entrada_caverna, FALSE);
	setVisivel(portal, TRUE);
	return colocaEmElemento(objeto, sul_caverna, getNome(obj));
}

unsigned short int entrarNoPortal(void* obj, void* IGNORAR2){
	if(!obj) return FALSE;
	printf("Parabéns, você ganhou o jogo!\n\n");
	GAME_OVER = TRUE;
	return TRUE;
}

void inicializa_jogo(){
	GAME_OVER = FALSE;

	unsigned short int res = TRUE;

	Elemento Lugar_inicial = criaLugar("ENTRADA DA CAVERNA", "Primeiro local do jogo", \
	"Você se encontra em uma caverna escura e fria, e se pergunta se está sozinho.\n\
Não é possível ver ninguém e sons de água corrente se ouvem mais para dentro da caverna.", TRUE, TRUE, FALSE);
	
	lugar_atual = Lugar_inicial;

	Aventureiro = criaAventureiro("AVENTUREIRO", "Finn, o Humano",\
	 "Finn é o último humano da terra de OOO. Junto com seu cão mágico Jake, eles\
partirão em busca de incríveis aventuras!");

	acoes_gerais = criaTabSim(TAM_TABSIM);

	sul_caverna = criaLugar("SUL DA CAVERNA", "Interior da caverna ao sul da entrada.", \
	"Você vê que a caverna está ficando mais clara. Há uma espécie de altar iluminado por tochas. No meio do altar há um ancião. Ele parece ciente da sua presença no lugar, e parece estar te esperando. Você pode tentar INTERAGIR.", \
	TRUE, TRUE, FALSE);

	Elemento anciao_sul_caverna = criaNPC("ANCIAO", "...", "Um ancião está em um altar, de olhos abertos e bem fixos em você, porém ele não aparenta ser uma ameaça. Parece que ele já esperava por você. Você pode tentar INTERAGIR.", \
	TRUE, TRUE, FALSE);

	saida_sul_entrada_caverna = criaSaida("SAIDA SUL", "Caminho para para dentro da caverna", \
		"Você avança para dentro da caverna.", TRUE, TRUE, FALSE, TRUE, sul_caverna);

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
por entre as árvores. O caminho é longo, mas você chega ao seu destino.", TRUE, TRUE, FALSE, TRUE, final);

	Elemento final_clareira = criaSaida("SUL", "Caminho para a CLAREIRA", "Você ruma de volta à CLAREIRA.", \
		TRUE, TRUE, FALSE, TRUE, clareira);

	Elemento floresta_clareira = criaSaida("OESTE", "Saída em direção à CLAREIRA", \
		"Você sai da FLORESTA em direção à CLAREIRA.", TRUE, TRUE, FALSE, TRUE, clareira);

	Elemento clareira_floresta = criaSaida("LESTE", "Saída em direção à FLORESTA", \
		"Você sai da CLAREIRA em direção à FLORESTA.", TRUE, TRUE, FALSE, TRUE, floresta);	

	Elemento en_cav_floresta = criaSaida("NORTE", "Saída em direção à FLORESTA", \
		"Você sai da ENTRADA DA CAVERNA em direção à FLORESTA.", TRUE, TRUE, FALSE, TRUE, floresta);

	Elemento floresta_en_cav = criaSaida("SUL", "Saída em direção à ENTRADA DA CAVERNA", \
		"Você avança ao SUL, em direção à ENTRADA DA CAVERNA.", TRUE, TRUE, FALSE, TRUE, Lugar_inicial);	


	res = colocaEmElemento(portal, final, "PORTAL");
	res = addSaida(floresta, floresta_clareira, "OESTE");
	res = addSaida(clareira, clareira_floresta, "LESTE");
	res = addSaida(clareira, clareira_final, "NORTE");
	res = addSaida(final, final_clareira, "SUL");	

	Elemento saida_norte_sul_caverna = criaSaida("NORTE", "Saída em direção à ENTRADA DA CAVERNA", \
		"Você anda rumo ao norte, para a ENTRADA DA CAVERNA.", TRUE, TRUE, FALSE, TRUE, Lugar_inicial);

	res = addSaida(sul_caverna, saida_norte_sul_caverna, "NORTE");
	res = addSaida(floresta, floresta_en_cav, "SUL");
	res = addSaida(Lugar_inicial, en_cav_floresta, "NORTE");
	res = addSaida(Lugar_inicial, saida_sul_entrada_caverna, "SUL");
	res = colocaEmElemento(Aventureiro, Lugar_inicial, "AVENTUREIRO");
	res = colocaEmElemento(anciao_sul_caverna, sul_caverna, "ANCIAO");
	res = colocaEmElemento(escalibur, anciao_sul_caverna, "ESPADA");	

	insereNaTabela(acoes_gerais, "CHORE",		chorar);
	insereNaTabela(acoes_gerais, "PEGUE",		pegarObj);
	insereNaTabela(acoes_gerais, "EXAMINE",		mostrarItem);
	insereNaTabela(acoes_gerais, "CONTEUDO",	listar);
	insereNaTabela(acoes_gerais, "LARGUE",		largar);
	insereNaTabela(acoes_gerais, "VA",			mover);
	insereNaTabela(acoes_gerais, "DESCREVA",	descreverLugar);

	carregaVerbo(anciao_sul_caverna,	interagirComAnciao, "FALE");
	carregaVerbo(clareira,				jogar,				"JOGUE");
	carregaVerbo(portal,				entrarNoPortal,		"ENTRE");

	printf("\n");
}