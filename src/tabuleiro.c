#include "tabuleiro.h"

#include <stdio.h>

void definir_casa(Casa *c, TipoDeCasa tipo, int indice){
	c->visitada = 0;
	c->evento = tipo;
	c->indice_monstro = indice;

}

void montar_tabuleiro(Tabuleiro *t, int fase){
	t->fase_atual = fase;
	t->missao_concluida = 0;
	t->posicao_player = 0;

	definir_casa(&t->casas[0], CASA_VAZIA, -1);
	definir_casa(&t->casas[1], CASA_COMBATE, 0);
	definir_casa(&t->casas[2], CASA_VAZIA, -1);
	definir_casa(&t->casas[3], CASA_TESOURO, -1);
	definir_casa(&t->casas[4], CASA_COMBATE, 1);
	definir_casa(&t->casas[5], CASA_CURA, -1);
	definir_casa(&t->casas[6], CASA_ARMADILHA, -1);
	definir_casa(&t->casas[7], CASA_COMBATE, 2);
	definir_casa(&t->casas[8], CASA_MISSAO, -1);
	definir_casa(&t->casas[9], CASA_TESOURO, -1);
	definir_casa(&t->casas[10], CASA_COMBATE, 1);
	definir_casa(&t->casas[11], CASA_CHEFE, 3);

}

static char *nome_da_casa(TipoDeCasa tipo){
	switch(tipo){
		case CASA_VAZIA:
			return "VAZIA";

		case CASA_COMBATE:
			return "COMBATE";

		case CASA_TESOURO:
			return "TESOURO";

		case CASA_CURA:
			return "CURA";

		case CASA_ARMADILHA:
			return "ARMADILHA";

		case CASA_MISSAO:
			return "MISSAO";

		case CASA_CHEFE:
			return "CHEFE";

		default:
            		return "DESCONHECIDO";
	}

}


void mostrar_tabuleiro(Tabuleiro *t) {

    const char *nome_fase;

    /* Identifica o nome da fase */

    switch (t->fase_atual) {

        case 1:
            nome_fase = "MUNDO DOS VIVOS";
            break;

        case 2:
            nome_fase = "HUECO MUNDO";
            break;

        case 3:
            nome_fase = "VALE DOS GRITOS";
            break;

        default:
            nome_fase = "REGIAO DESCONHECIDA";
            break;
    }

    printf("\n");
    printf("===============================================================\n");
    printf("              BLEACH: ECHOES OF THE VOID\n");
    printf("                 FASE %d - %s\n", t->fase_atual, nome_fase);
    printf("===============================================================\n");

    printf("\n POSICAO ATUAL: CASA %02d DE %02d\n",
           t->posicao_player + 1, TAM_TABULEIRO);

    printf("\n");


    for (int inicio = 0; inicio < TAM_TABULEIRO; inicio += 4) {

        int quantidade = TAM_TABULEIRO - inicio;

        if (quantidade > 4) {
            quantidade = 4;
        }

        for (int j = 0; j < quantidade; j++) {
            printf("+----------------------");
        }
        printf("+\n");

        for (int j = 0; j < quantidade; j++) {

            int indice = inicio + j;
            char titulo[40];

            if (indice == t->posicao_player) {
                snprintf(titulo, sizeof(titulo),
                         "  CASA %02d  <P>", indice + 1);
            } else {
                snprintf(titulo, sizeof(titulo),
                         "  CASA %02d", indice + 1);
            }

            printf("|%-22.22s", titulo);
        }

        printf("|\n");

        for (int j = 0; j < quantidade; j++) {

            int indice = inicio + j;
            char evento[40];

            snprintf(evento, sizeof(evento),
                     "  EVENTO: %s",
                     nome_da_casa(t->casas[indice].evento));

            printf("|%-22.22s", evento);
        }

        printf("|\n");

        for (int j = 0; j < quantidade; j++) {
            printf("+----------------------");
        }
        printf("+\n");
    }


    printf("\n LEGENDA:\n");
    printf(" <P>       = Sua posicao atual\n");
    printf(" COMBATE   = Inimigo\n");
    printf(" TESOURO   = Recompensa\n");
    printf(" CURA      = Recuperacao de vida\n");
    printf(" ARMADILHA = Perigo\n");
    printf(" MISSAO    = Objetivo da fase\n");
    printf(" CHEFE     = Batalha especial\n");
    printf(" VAZIA     = Nenhum evento\n");

    printf("\n===============================================================\n");
}
