
#include <stdio.h>
#include <stdlib.h>

#include "jogo.h"

#include "personagem.h"

#include "tabuleiro.h"

#include "menu.h"

static void introducao_fase_um(Personagem *p);
static void lore_missao_fase_um(Personagem *p);

static void introducao_fase_dois(Personagem *p);
static void lore_missao_fase_dois(Personagem *p);

static void introducao_fase_tres(Personagem *p);
static void lore_missao_fase_tres(Personagem *p);


int rolar_dado(int lados){

	return rand() % lados + 1;
}

void executar_evento(Personagem *p, Tabuleiro *t){
	switch(t->casas[t->posicao_player].evento){
		case CASA_VAZIA:
			printf("mensagem da lore");
			t->casas[t->posicao_player].visitada = 1;
			break;
		case CASA_TESOURO:
			ganhar_xp(p , XP_TESOURO);
			printf("VOCE ACHOU UM TESOURO !\n GANHOU %d XP\n", XP_TESOURO);
			t->casas[t->posicao_player].visitada = 1;
			break;
		case CASA_CURA:{
			int quantidade = p->vida_maxima * 25 / 100;

			if((p->vida_maxima - p->vida_atual) < quantidade){
				quantidade = p->vida_maxima - p->vida_atual;
			}

			curar(p , quantidade);

			printf("VOCE ENCONTROU UMA CURA !\n RECUPEROU %d DE VIDA\n", quantidade);
			t->casas[t->posicao_player].visitada = 1;
                        break;
		}
		case CASA_ARMADILHA:{
			int quantidade = p->vida_maxima * 10 / 100;
			receber_dano(p, quantidade);
			t->casas[t->posicao_player].visitada = 1;
			printf("VOCE CAIU EM UMA ARMADILHA !\n PERDEU %d HP\n", quantidade);
                        break;
		}
		case CASA_MISSAO:
		    switch (t->fase_atual) {

        		case 1:
            			lore_missao_fase_um(p);
            			break;

        		case 2:
            			lore_missao_fase_dois(p);
            			break;

        		case 3:
            			lore_missao_fase_tres(p);
            			break;

        		default:
            			printf("MISSÃO DA FASE NÃO ENCONTRADA!\n");
            			break;
		    }

    			t->missao_concluida = 1;
    			t->casas[t->posicao_player].visitada = 1;
    			break;
		case CASA_COMBATE:
			printf("combate iniciado");
			break;
		case CASA_CHEFE:
			printf("combate contra o chefe");
			break;
	}

}



ResultadoFase jogar_fase(Personagem *p, Tabuleiro *t){

	switch (t->fase_atual) {

    		case 1:
       			introducao_fase_um(p);
        		break;

    		case 2:
        		introducao_fase_dois(p);
        		break;

    		case 3:
        		introducao_fase_tres(p);
        		break;
	}


	while((p->vida_atual > 0) && (t->posicao_player < (TAM_TABULEIRO - 1))){

		limpar_terminal();

		mostrar_personagem(p);
		mostrar_tabuleiro(t);

		printf("press ENTER para rolar o dado\n");

		pausar();

		int passos = rolar_dado(DADO_MOVIMENTACAO);

		mover_personagem(t,passos);

		limpar_terminal();

		printf("VOCE TIROU --> %d <-- NO DADO\n", passos);

		executar_evento(p, t);

		printf("\nPressione ENTER para continuar...\n");
                pausar();

	}

	if(p->vida_atual <= 0){
		return RESULTADO_FASE_DERROTA;
	}

	else{
		return RESULTADO_FASE_CONCLUIDA;
	}


}

static void introducao_fase_um(Personagem *p) {

    limpar_terminal();

    printf("\n");
    printf("============================================================\n");
    printf("                BLEACH: ECHOES OF THE VOID\n");
    printf("============================================================\n");
    printf("press ENTER para aparecer o texto...");
    pausar();

    printf("\n");
    printf("                 FASE 01 - MUNDO DOS VIVOS\n");
    printf("                       KARAKURA - 23:47\n");
    printf("\n");
    pausar();

    printf("A noite parecia tranquila em Karakura...\n");
    printf("Mas algo estava prestes a mudar.\n\n");
    pausar();

    printf("Nos ultimos dias, acontecimentos estranhos passaram a\n");
    printf("assombrar a regiao. Almas permanecem no mundo dos vivos\n");
    printf("por mais tempo que o normal, enquanto Hollows demonstram\n");
    printf("uma agressividade nunca antes observada.\n\n");
    pausar();

    printf("Na Soul Society, os registros espirituais apontam para\n");
    printf("irregularidades no fluxo das almas. Algo desconhecido\n");
    printf("parece estar interferindo no equilibrio entre os mundos.\n\n");
    pausar();

    printf("Entretanto, naquela noite, o fenomeno se intensifica.\n");
    printf("Uma onda de energia espiritual atravessa Karakura.\n\n");
    pausar();

    printf("Por alguns instantes, tudo parece perder o sentido.\n");
    printf("Os Hollows ao redor ficam descontrolados. Uma presenca\n");
    printf("desconhecida parece chamar e absorver a energia espiritual\n");
    printf("das almas proximas.\n\n");
    pausar();

    printf("Voce sente aquela pressao espiritual se aproximando.\n");
    printf("Algo tenta invadir sua consciencia...\n");
    pausar();

    switch (p->classe) {

        case CLASSE_SHINIGAMI:

            printf("\nSua Zanpakuto comeca a vibrar intensamente.\n");
            printf("Por um instante, voce sente uma presenca estranha\n");
            printf("vinda de sua propria espada.\n");
            printf("Mesmo diante daquela pressao, voce permanece consciente.\n");
            break;

        case CLASSE_QUINCY:

            printf("\nVoce percebe que as particulas espirituais ao seu\n");
            printf("redor estao sendo atraidas para uma direcao especifica.\n");
            printf("Algo parece estar absorvendo o Reishi da regiao.\n");
            printf("Mesmo assim, sua consciencia permanece intacta.\n");
            break;

        case CLASSE_HOLLOW:

            printf("\nOs Hollows proximos parecem perder completamente\n");
            printf("o controle de seus instintos. Uma fome espiritual\n");
            printf("anormal toma conta das criaturas.\n");
            printf("Mas, diferentemente deles, voce consegue resistir.\n");
            break;
    }
    pausar();

    printf("\n");
    printf("============================================================\n");
    printf("                    UMA PRESENCA INESPERADA\n");
    printf("============================================================\n\n");
    pausar();

    printf("Uma voz surge atras de voce.\n\n");
    pausar();

    printf("KISUKE URAHARA:\n\n");
    pausar();

    printf("\"Interessante... Voce tambem sentiu essa energia,\n");
    printf("nao foi?\"\n\n");
    pausar();

    printf("\"Estou investigando essas anomalias ha algum tempo.\n");
    printf("Hollows estao agindo de maneira incomum, e o fluxo\n");
    printf("das almas parece estar sendo alterado.\"\n\n");
    pausar();

    printf("\"Mas existe algo ainda mais estranho...\"\n\n");
    pausar();

    printf("\"Aquela energia tentou dominar sua consciencia.\n");
    printf("E, mesmo assim, voce permaneceu de pe.\"\n\n");
    pausar();

    printf("Urahara observa a regiao em silencio por alguns instantes.\n");
    printf("Sua expressao muda. Ele parece ter percebido algo.\n\n");
    pausar();

    printf("KISUKE URAHARA:\n\n");

    printf("\"Seja la o que estiver acontecendo, tenho a impressao\n");
    printf("de que estamos apenas no comeco.\"\n\n");
    pausar();

    printf("\"Preciso descobrir de onde vem essa energia.\n");
    printf("E acredito que voce pode me ajudar.\"\n\n");
    pausar();

    printf("============================================================\n");
    printf("                     MISSAO PRINCIPAL\n");
    printf("============================================================\n\n");
    pausar();

    printf("INVESTIGUE A ANOMALIA ESPIRITUAL EM KARAKURA.\n\n");

    printf("Descubra a origem da energia desconhecida, investigue\n");
    printf("os Hollows corrompidos e descubra por que algumas almas\n");
    printf("estao desaparecendo.\n\n");
    pausar();

    printf("Sua resistencia a essa presenca pode ser a chave\n");
    printf("para compreender o que esta acontecendo.\n\n");
    pausar();

    printf("============================================================\n");
    printf("         SUA JORNADA COMECA AGORA, %s!\n", p->nome);
    printf("============================================================\n");
    pausar();

    printf("\nPressione ENTER para iniciar sua investigacao...");

    pausar();

}


static void lore_missao_fase_um(Personagem *p) {

    limpar_terminal();

    printf("\n");
    printf("============================================================\n");
    printf("                 KARAKURA - INVESTIGACAO\n");
    printf("============================================================\n\n");
    pausar();

    printf("Seguindo os rastros espirituais, voce chega a uma regiao\n");
    printf("isolada de Karakura.\n\n");
    pausar();

    printf("O ambiente esta silencioso. A energia espiritual parece\n");
    printf("mais intensa naquele local.\n\n");
    pausar();

    printf("No chao, voce encontra marcas de combate e fragmentos\n");
    printf("de uma Zanpakuto.\n\n");
    pausar();

    printf("Algo chama sua atencao: a energia deixada naquele local\n");
    printf("nao pertence a um Hollow comum.\n\n");
    pausar();

    printf("De repente, seu comunicador emite um sinal.\n\n");
    pausar();

    printf("KISUKE URAHARA:\n\n");
    pausar();

    printf("\"Conseguiu encontrar alguma coisa?\"\n\n");
    pausar();

    printf("\"Estive analisando os rastros espirituais que voce\n");
    printf("encontrou. Essa energia parece estar absorvendo almas\n");
    printf("e alterando o fluxo espiritual da regiao.\"\n\n");
    pausar();

    printf("\"Mas existe algo ainda mais preocupante...\"\n\n");
    pausar();

    printf("\"Encontrei registros de uma frequencia semelhante\n");
    printf("vinda de um Shinigami.\"\n\n");
    pausar();

    printf("\"Parece que alguns dos nossos proprios aliados\n");
    printf("tambem estao sendo afetados.\"\n\n");
    pausar();

    printf("Uma onda de energia atravessa o local.\n");
    printf("Por um instante, voce sente novamente aquela presenca.\n\n");
    pausar();

    switch (p->classe) {

        case CLASSE_SHINIGAMI:
            printf("Sua Zanpakuto comeca a vibrar, reagindo a energia\n");
            printf("desconhecida presente no ambiente.\n");
            break;

        case CLASSE_QUINCY:
            printf("As particulas de Reishi ao seu redor oscilam\n");
            printf("violentamente, como se algo tentasse absorve-las.\n");
            break;

        case CLASSE_HOLLOW:
            printf("Seu instinto Hollow reage violentamente a energia.\n");
            printf("Mesmo assim, voce consegue manter o controle.\n");
            break;
    }

    printf("\n");
    pausar();

    printf("KISUKE URAHARA:\n\n");
    pausar();

    printf("\"Os rastros espirituais apontam para uma passagem\n");
    printf("entre os mundos.\"\n\n");
    pausar();

    printf("\"Nao sabemos o que existe do outro lado, mas acredito\n");
    printf("que encontraremos respostas por la.\"\n\n");
    pausar();

    printf("\"Tenha cuidado. Se essa energia esta afetando ate\n");
    printf("mesmo os Shinigamis, nao podemos subestimar o perigo.\"\n\n");
    pausar();

    printf("============================================================\n");
    printf("                    MISSAO CONCLUIDA!\n");
    printf("============================================================\n\n");
    pausar();

    printf("Voce descobriu que a anomalia esta afetando diferentes\n");
    printf("seres espirituais, inclusive os Shinigamis.\n\n");
    pausar();

    printf("Novos rastros foram encontrados. Sua proxima jornada\n");
    printf("o levara para alem do Mundo dos Vivos.\n\n");
    pausar();

    printf("============================================================\n");
    printf("                  FIM DA FASE 01\n");
    printf("============================================================\n\n");
    pausar();
}


static void introducao_fase_dois(Personagem *p) {

    limpar_terminal();

    printf("\n");
    printf("============================================================\n");
    printf("                 FASE 02 - HUECO MUNDO\n");
    printf("============================================================\n\n");
    pausar();

    printf("Apos atravessar a passagem entre os mundos, voce chega\n");
    printf("a uma vasta extensao de areia branca.\n\n");
    pausar();

    printf("O ceu escuro de Hueco Mundo parece ainda mais silencioso\n");
    printf("do que o normal.\n\n");
    pausar();

    printf("Entretanto, algo esta errado.\n\n");
    pausar();

    printf("Hollows abandonam seus territorios e se deslocam em\n");
    printf("direcao a uma regiao distante. Alguns parecem fugir\n");
    printf("de alguma coisa. Outros demonstram uma agressividade\n");
    printf("incontrolavel.\n\n");
    pausar();

    printf("Uma voz conhecida chama sua atencao.\n\n");
    pausar();

    printf("NELLIEL TU ODELSCHWANCK:\n\n");
    pausar();

    printf("\"Entao voce e a pessoa que Urahara mencionou.\"\n\n");
    pausar();

    printf("\"Tenho observado o comportamento dos Hollows ha algum\n");
    printf("tempo. Algo esta forcando essas criaturas a abandonar\n");
    printf("seus territorios.\"\n\n");
    pausar();

    printf("\"A energia que sentimos vem de uma regiao mais distante.\n");
    printf("Mas nao consigo identificar sua verdadeira origem.\"\n\n");
    pausar();

    printf("Antes que a conversa continue, uma forte pressao espiritual\n");
    printf("surge nas proximidades.\n\n");
    pausar();

    printf("GRIMMJOW JAEGERJAQUE:\n\n");
    pausar();

    printf("\"Tch... Entao voces tambem estao atras dessa coisa?\"\n\n");
    pausar();

    printf("\"Nao estou interessado em trabalhar em equipe. Mas tem\n");
    printf("algo naquela direcao que esta me incomodando.\"\n\n");
    pausar();

    printf("\"Seja la o que for, vou acabar com isso.\"\n\n");
    pausar();

    printf("Grimmjow segue em direcao a concentracao de energia,\n");
    printf("sem esperar pelos demais.\n\n");
    pausar();

    printf("NELLIEL:\n\n");
    pausar();

    printf("\"Ele sempre foi assim. Mas talvez seja melhor mantermos\n");
    printf("os olhos abertos. Nao sabemos o que vamos encontrar.\"\n\n");
    pausar();

    switch (p->classe) {

        case CLASSE_SHINIGAMI:
            printf("Sua Zanpakuto reage novamente. A vibracao parece\n");
            printf("mais intensa do que aquela sentida em Karakura.\n");
            break;

        case CLASSE_QUINCY:
            printf("O Reishi ao seu redor se movimenta de maneira irregular.\n");
            printf("A concentracao de energia parece alterar todo o ambiente.\n");
            break;

        case CLASSE_HOLLOW:
            printf("Seu instinto reconhece algo naquela direcao.\n");
            printf("Uma presenca poderosa parece chamar todos os Hollows.\n");
            break;
    }

    printf("\n");
    pausar();

    printf("============================================================\n");
    printf("                     NOVA INVESTIGACAO\n");
    printf("============================================================\n\n");
    pausar();

    printf("INVESTIGUE A CONCENTRACAO DE ENERGIA EM HUECO MUNDO.\n\n");

    printf("Descubra por que os Hollows estao abandonando seus\n");
    printf("territorios e encontre a origem da energia desconhecida.\n\n");
    pausar();

    printf("NELLIEL E GRIMMJOW SEGUIRAO OS RASTROS POR CAMINHOS\n");
    printf("DIFERENTES. ENCONTRE-SE COM ELES DURANTE A INVESTIGACAO.\n\n");
    pausar();

    printf("============================================================\n");
    printf("              A INVESTIGACAO CONTINUA...\n");
    printf("============================================================\n");
    pausar();
}



static void lore_missao_fase_dois(Personagem *p) {

    limpar_terminal();

    printf("\n");
    printf("============================================================\n");
    printf("              HUECO MUNDO - PONTO DE CONVERGENCIA\n");
    printf("============================================================\n\n");
    pausar();

    printf("Depois de seguir os rastros, voce chega a uma regiao\n");
    printf("onde a energia espiritual parece estar concentrada.\n\n");
    pausar();

    printf("A areia ao redor apresenta marcas de movimentacao.\n");
    printf("Diversos Hollows passaram por aquele lugar.\n\n");
    pausar();

    printf("NELLIEL:\n\n");
    pausar();

    printf("\"E aqui... Todos os rastros parecem terminar neste ponto.\"\n\n");
    pausar();

    printf("\"Mas existe algo estranho. Essa energia nao parece\n");
    printf("pertencer a nenhum Hollow que conhecemos.\"\n\n");
    pausar();

    printf("Dondochakka e Pesche se aproximam, trazendo informacoes\n");
    printf("que conseguiram reunir durante a investigacao.\n\n");
    pausar();

    printf("PESCHE:\n\n");
    pausar();

    printf("\"Encontramos marcas semelhantes em outras regioes!\n");
    printf("Todas apontam para uma mesma direcao!\"\n\n");
    pausar();

    printf("DONDOCCHAKKA:\n\n");
    pausar();

    printf("\"E nao sao apenas os Hollows comuns que estao seguindo\n");
    printf("esse caminho. Existe algo muito maior acontecendo!\"\n\n");
    pausar();

    printf("Uma forte pressao espiritual interrompe a conversa.\n\n");
    pausar();

    printf("GRIMMJOW:\n\n");
    pausar();

    printf("\"Hmph. Finalmente entenderam?\"\n\n");
    pausar();

    printf("\"Aquela coisa nao esta simplesmente atraindo os Hollows.\n");
    printf("Esta usando a energia deles para alguma finalidade.\"\n\n");
    pausar();

    printf("Voce observa a concentracao espiritual mais uma vez.\n");
    printf("Por um instante, consegue perceber que ela nao termina\n");
    printf("naquele local.\n\n");
    pausar();

    printf("Existe um caminho levando a uma regiao ainda mais distante.\n\n");
    pausar();

    printf("NELLIEL:\n\n");
    pausar();

    printf("\"Conheco essa direcao...\"\n\n");
    pausar();

    printf("\"Ela leva ao Vale dos Gritos. Um lugar instavel, formado\n");
    printf("por fragmentos de espacos que foram separados dos mundos.\"\n\n");
    pausar();

    printf("\"Se a energia esta vindo de la, talvez encontremos\n");
    printf("a origem de tudo isso.\"\n\n");
    pausar();

    switch (p->classe) {

        case CLASSE_SHINIGAMI:
            printf("Sua Zanpakuto permanece vibrando. Parece reagir\n");
            printf("a algo que existe alem daquela regiao.\n");
            break;

        case CLASSE_QUINCY:
            printf("Voce percebe que o fluxo de Reishi segue em direcao\n");
            printf("ao Vale dos Gritos, como se estivesse sendo conduzido.\n");
            break;

        case CLASSE_HOLLOW:
            printf("Seu instinto Hollow identifica uma presenca distante.\n");
            printf("Ela parece muito mais antiga e poderosa que os Hollows\n");
            printf("que encontrou ate agora.\n");
            break;
    }

    printf("\n");
    pausar();

    printf("============================================================\n");
    printf("                    MISSAO CONCLUIDA!\n");
    printf("============================================================\n\n");
    pausar();

    printf("Voce descobriu que a energia esta sendo direcionada\n");
    printf("para o Vale dos Gritos.\n\n");
    pausar();

    printf("A origem da anomalia continua desconhecida, mas agora\n");
    printf("existe um caminho para encontrar respostas.\n\n");
    pausar();

    printf("============================================================\n");
    printf("                  FIM DA FASE 02\n");
    printf("============================================================\n\n");
    pausar();
}


static void introducao_fase_tres(Personagem *p) {

    limpar_terminal();

    printf("\n");
    printf("============================================================\n");
    printf("                 FASE 03 - VALE DOS GRITOS\n");
    printf("============================================================\n\n");
    pausar();

    printf("A passagem leva voce a um lugar completamente diferente.\n\n");
    pausar();

    printf("O Vale dos Gritos se estende diante dos seus olhos.\n");
    printf("Fragmentos de terrenos, estruturas e ruinas parecem\n");
    printf("existir fora de qualquer ordem natural.\n\n");
    pausar();

    printf("O ambiente parece instavel. O proprio espaco ao redor\n");
    printf("sofre pequenas distorcoes.\n\n");
    pausar();

    printf("A energia espiritual e muito mais intensa do que tudo\n");
    printf("que voce encontrou nas outras regioes.\n\n");
    pausar();

    printf("NELLIEL:\n\n");
    pausar();

    printf("\"Este lugar guarda fragmentos de diferentes regioes.\n");
    printf("Poucos conhecem sua verdadeira origem.\"\n\n");
    pausar();

    printf("\"Mas existe algo aqui... Algo que parece ter despertado\n");
    printf("depois de permanecer adormecido por muito tempo.\"\n\n");
    pausar();

    printf("GRIMMJOW:\n\n");
    pausar();

    printf("\"Tch... Nao preciso que me expliquem o perigo.\"\n\n");
    pausar();

    printf("\"Essa pressao espiritual e diferente de tudo que ja senti.\"\n\n");
    pausar();

    printf("Voce avanca alguns passos. De repente, a energia ao redor\n");
    printf("parece reagir diretamente a sua presenca.\n\n");
    pausar();

    switch (p->classe) {

        case CLASSE_SHINIGAMI:
            printf("Sua Zanpakuto comeca a vibrar de maneira descontrolada.\n");
            printf("Uma sensacao familiar surge, como se sua espada\n");
            printf("reconhecesse aquela energia.\n");
            break;

        case CLASSE_QUINCY:
            printf("O Reishi ao seu redor converge em sua direcao.\n");
            printf("Por alguns instantes, voce percebe uma frequencia\n");
            printf("semelhante a que sentiu em Karakura.\n");
            break;

        case CLASSE_HOLLOW:
            printf("Seu instinto Hollow reage intensamente.\n");
            printf("A presenca naquele lugar parece reconhecer voce,\n");
            printf("mas voce continua no controle de sua consciencia.\n");
            break;
    }

    printf("\n");
    pausar();

    printf("Uma voz surge em sua mente.\n\n");
    pausar();

    printf("\"Finalmente... voce chegou ate aqui.\"\n\n");
    pausar();

    printf("A voz desaparece. Mas a sensacao de estar sendo\n");
    printf("observado permanece.\n\n");
    pausar();

    printf("NELLIEL:\n\n");
    pausar();

    printf("\"Voce sentiu isso tambem, nao foi?\"\n\n");
    pausar();

    printf("\"Precisamos descobrir o que existe nestas ruinas.\n");
    printf("Acredito que encontraremos nossas respostas aqui.\"\n\n");
    pausar();

    printf("============================================================\n");
    printf("                  ULTIMA INVESTIGACAO\n");
    printf("============================================================\n\n");
    pausar();

    printf("INVESTIGUE AS RUINAS ANTIGAS DO VALE DOS GRITOS.\n\n");

    printf("Descubra a origem da energia desconhecida e a identidade\n");
    printf("da presenca que vem interferindo nos tres mundos.\n\n");
    pausar();

    printf("Algo neste lugar parece estar conectado a voce.\n\n");
    pausar();

    printf("============================================================\n");
    printf("              A VERDADE ESTA PROXIMA...\n");
    printf("============================================================\n");
    pausar();
}


static void lore_missao_fase_tres(Personagem *p) {

    limpar_terminal();

    printf("\n");
    printf("============================================================\n");
    printf("             VALE DOS GRITOS - RUINAS ANTIGAS\n");
    printf("============================================================\n\n");
    pausar();

    printf("Ao explorar as ruinas, voce encontra uma estrutura antiga\n");
    printf("que parece ter permanecido escondida por seculos.\n\n");
    pausar();

    printf("Simbolos desconhecidos cobrem as paredes. A energia\n");
    printf("espiritual naquele local e extremamente intensa.\n\n");
    pausar();

    printf("NELLIEL:\n\n");
    pausar();

    printf("\"Essas inscricoes... Nunca vi nada parecido.\"\n\n");
    pausar();

    printf("\"Parece que este lugar ja existia muito antes das\n");
    printf("estruturas que conhecemos atualmente.\"\n\n");
    pausar();

    printf("Seu comunicador emite um sinal. A voz de Urahara surge,\n");
    printf("com dificuldade para atravessar a distorcao espiritual.\n\n");
    pausar();

    printf("KISUKE URAHARA:\n\n");
    pausar();

    printf("\"Consegui analisar parte dos registros enviados por voce.\"\n\n");
    pausar();

    printf("\"O que encontramos pode ser muito mais antigo do que\n");
    printf("imaginavamos. As inscricoes fazem referencia a uma epoca\n");
    printf("em que os tres mundos ainda formavam uma unica existencia.\"\n\n");
    pausar();

    printf("\"Quando os mundos foram separados, algo foi dividido\n");
    printf("junto com aquela antiga realidade.\"\n\n");
    pausar();

    printf("\"Se minha interpretacao estiver correta, parte desses\n");
    printf("fragmentos foi lancada na Garganta. Outros acabaram\n");
    printf("presos neste vale.\"\n\n");
    pausar();

    printf("De repente, as ruinas comecam a vibrar.\n");
    printf("A energia espiritual se concentra no centro da estrutura.\n\n");
    pausar();

    printf("Uma voz profunda ecoa pelo ambiente.\n\n");
    pausar();

    printf("\"Chega de procurar. Finalmente posso revelar minha identidade.\"\n\n");
    pausar();

    printf("APARICION:\n\n");
    pausar();

    printf("\"Antes da separacao dos mundos, nos eramos uma unica existencia.\"\n\n");
    pausar();

    printf("\"Quando essa realidade foi dividida, eu tambem fui fragmentado.\"\n\n");
    pausar();

    printf("\"Durante seculos, permaneci adormecido, espalhado entre\n");
    printf("os fragmentos que foram esquecidos neste vazio.\"\n\n");
    pausar();

    printf("\"Mas agora estou despertando. E os tres mundos sentirao\n");
    printf("novamente a minha presenca.\"\n\n");
    pausar();

    printf("A energia ao redor comeca a se movimentar em direcao\n");
    printf("aquela presenca.\n\n");
    pausar();

    printf("APARICION:\n\n");
    pausar();

    printf("\"Os Hollows, as almas e ate mesmo os Shinigamis...\"\n\n");
    pausar();

    printf("\"Todos podem servir como fonte para recuperar aquilo\n");
    printf("que foi retirado de mim.\"\n\n");
    pausar();

    printf("\"Preciso recuperar minha existencia. E, quando estiver\n");
    printf("completo, os tres mundos finalmente deixarao de existir.\"\n\n");
    pausar();

    printf("NELLIEL:\n\n");
    pausar();

    printf("\"Voce pretende destruir todos os mundos?!\"\n\n");
    pausar();

    printf("APARICION:\n\n");
    pausar();

    printf("\"Observe a existencia de voces.\"\n\n");
    pausar();

    printf("\"As almas continuam presas em um ciclo de sofrimento.\n");
    printf("A vida, a morte e a destruicao se repetem sem fim.\"\n\n");
    pausar();

    printf("\"A separacao dos mundos nunca trouxe equilibrio.\n");
    printf("Apenas prolongou esse sofrimento.\"\n\n");
    pausar();

    printf("\"Quando tudo terminar, nao havera mais ciclos.\n");
    printf("Nao havera mais dor.\"\n\n");
    pausar();

    printf("A presenca volta sua atencao diretamente para voce.\n\n");
    pausar();

    printf("APARICION:\n\n");
    pausar();

    printf("\"Mas voce... Existe algo diferente em voce.\"\n\n");
    pausar();

    printf("\"%s... Desde nosso primeiro contato, sua consciencia\n", p->nome);
    printf("resistiu a minha influencia. Isso nao foi algo comum.\"\n\n");

    printf("\"Sua existencia possui uma ligacao com os fragmentos\n");
    printf("que foram espalhados quando os mundos se separaram.\"\n\n");
    pausar();

    printf("\"Voce poderia ser o recipiente que me permitiria\n");
    printf("recuperar minha forma completa.\"\n\n");
    pausar();

    printf("\"Junte-se a mim. Podemos acabar com esse ciclo de uma vez.\"\n\n");
    pausar();

    printf("Por alguns instantes, o ambiente permanece em silencio.\n");
    printf("Agora voce compreende a origem das anomalias.\n\n");
    pausar();

    printf("A energia que atraiu os Hollows, corrompeu os Shinigamis\n");
    printf("e alterou o fluxo das almas tinha uma unica origem.\n\n");
    pausar();

    printf("APARICION deseja recuperar sua forma completa utilizando\n");
    printf("a energia espiritual dos tres mundos.\n\n");
    pausar();

    printf("Mas voce nao pretende permitir que isso aconteca.\n\n");
    pausar();

    printf("============================================================\n");
    printf("                    MISSAO CONCLUIDA!\n");
    printf("============================================================\n\n");
    pausar();

    printf("A identidade e os objetivos de Aparicion foram revelados.\n\n");
    pausar();

    printf("Agora resta impedir que a entidade recupere sua forma\n");
    printf("completa e destrua os tres mundos.\n\n");
    pausar();

    printf("============================================================\n");
    printf("                 O CONFRONTO FINAL SE APROXIMA\n");
    printf("============================================================\n\n");
    pausar();

    printf("Aparicion aguarda adiante.\n");
    printf("Sua jornada chegara ao fim neste lugar.\n\n");
    pausar();

}
