#include <stdio.h>
#include <stdlib.h>

#include "jogo.h"

#include "personagem.h"

#include "menu.h"

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
			curar(p , quantidade);

			if((p->vida_maxima - p->vida_atual) < quantidade){
				quantidade = p->vida_maxima - p->vida_atual;
			}

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
			printf("objetivo da missao");
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

}

static void introducao_fase_um(Personagem *p) {

    limpar_terminal();

    printf("\n");
    printf("============================================================\n");
    printf("                BLEACH: ECHOES OF THE VOID\n");
    printf("============================================================\n");

    printf("\n");
    printf("                 FASE 01 - MUNDO DOS VIVOS\n");
    printf("                       KARAKURA - 23:47\n");
    printf("\n");

    printf("A noite parecia tranquila em Karakura...\n");
    printf("Mas algo estava prestes a mudar.\n\n");

    printf("Nos ultimos dias, acontecimentos estranhos passaram a\n");
    printf("assombrar a regiao. Almas permanecem no mundo dos vivos\n");
    printf("por mais tempo que o normal, enquanto Hollows demonstram\n");
    printf("uma agressividade nunca antes observada.\n\n");

    printf("Na Soul Society, os registros espirituais apontam para\n");
    printf("irregularidades no fluxo das almas. Algo desconhecido\n");
    printf("parece estar interferindo no equilibrio entre os mundos.\n\n");

    printf("Entretanto, naquela noite, o fenomeno se intensifica.\n");
    printf("Uma onda de energia espiritual atravessa Karakura.\n\n");

    printf("Por alguns instantes, tudo parece perder o sentido.\n");
    printf("Os Hollows ao redor ficam descontrolados. Uma presenca\n");
    printf("desconhecida parece chamar e absorver a energia espiritual\n");
    printf("das almas proximas.\n\n");

    printf("Voce sente aquela pressao espiritual se aproximando.\n");
    printf("Algo tenta invadir sua consciencia...\n");

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

    printf("\n");
    printf("============================================================\n");
    printf("                    UMA PRESENCA INESPERADA\n");
    printf("============================================================\n\n");

    printf("Uma voz surge atras de voce.\n\n");

    printf("KISUKE URAHARA:\n\n");

    printf("\"Interessante... Voce tambem sentiu essa energia,\n");
    printf("nao foi?\"\n\n");

    printf("\"Estou investigando essas anomalias ha algum tempo.\n");
    printf("Hollows estao agindo de maneira incomum, e o fluxo\n");
    printf("das almas parece estar sendo alterado.\"\n\n");

    printf("\"Mas existe algo ainda mais estranho...\"\n\n");

    printf("\"Aquela energia tentou dominar sua consciencia.\n");
    printf("E, mesmo assim, voce permaneceu de pe.\"\n\n");

    printf("Urahara observa a regiao em silencio por alguns instantes.\n");
    printf("Sua expressao muda. Ele parece ter percebido algo.\n\n");

    printf("KISUKE URAHARA:\n\n");

    printf("\"Seja la o que estiver acontecendo, tenho a impressao\n");
    printf("de que estamos apenas no comeco.\"\n\n");

    printf("\"Preciso descobrir de onde vem essa energia.\n");
    printf("E acredito que voce pode me ajudar.\"\n\n");

    printf("============================================================\n");
    printf("                     MISSAO PRINCIPAL\n");
    printf("============================================================\n\n");

    printf("INVESTIGUE A ANOMALIA ESPIRITUAL EM KARAKURA.\n\n");

    printf("Descubra a origem da energia desconhecida, investigue\n");
    printf("os Hollows corrompidos e descubra por que algumas almas\n");
    printf("estao desaparecendo.\n\n");

    printf("Sua resistencia a essa presenca pode ser a chave\n");
    printf("para compreender o que esta acontecendo.\n\n");

    printf("============================================================\n");
    printf("         SUA JORNADA COMECA AGORA, %s!\n", p->nome);
    printf("============================================================\n");

    printf("\nPressione ENTER para iniciar sua investigacao...");

    pausar();

}
