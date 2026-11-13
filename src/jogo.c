
#include <stdio.h>
#include <stdlib.h>

#include "monstros.h"

#include "jogo.h"

#include "personagem.h"

#include "tabuleiro.h"

#include "menu.h"




#include "historia.h"

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
        case CASA_COMBATE: {
            Monstro monstro;

            int indice = t->casas[t->posicao_player].indice_monstro;

            criar_monstro(&monstro, t->fase_atual, indice);

            printf("\nUM INIMIGO APARECEU!\n\n");
            printf("Nome: %s\n", monstro.nome);
            printf("Descricao: %s\n", monstro.descricao);
            printf("Vida: %d/%d\n", monstro.vida_atual,
                monstro.vida_maxima);

            break;
        }
        case CASA_CHEFE: {
            Monstro monstro;

            int indice =
                t->casas[t->posicao_player].indice_monstro;

            criar_monstro(&monstro, t->fase_atual, indice);

            printf("\n========================================\n");
            printf("             CHEFE DA FASE\n");
            printf("========================================\n\n");

            printf("Nome: %s\n", monstro.nome);
            printf("Descricao: %s\n", monstro.descricao);
            printf("Vida: %d/%d\n",
                   monstro.vida_atual, monstro.vida_maxima);

            break;
        }

    } 

} 


ResultadoFase jogar_fase(Personagem *p, Tabuleiro *t) {

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


