
#include <stdio.h>
#include <stdlib.h>

#include "jogo.h"

#include "personagem.h"

#include "tabuleiro.h"

#include "menu.h"

static void introducao_fase_um(Personagem *p);

static void lore_missao_fase_um(Personagem *p);


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
    			if (t->fase_atual == 1) {
        			lore_missao_fase_um(p);
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

        if(t->fase_atual == 1){
		introducao_fase_um(p);
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

