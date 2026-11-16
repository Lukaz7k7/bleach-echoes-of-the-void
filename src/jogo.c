
#include <stdio.h>
#include <stdlib.h>

#include "monstros.h"

#include "jogo.h"

#include "personagem.h"

#include "tabuleiro.h"

#include "menu.h"

#include "combate.h"

#include "progressao.h"



#include "historia.h"

int rolar_dado(int lados){

	return rand() % lados + 1;
}

void executar_evento(Personagem *p, Tabuleiro *t){
	switch(t->casas[t->posicao_player].evento){

		case CASA_VAZIA:
            switch (t->fase_atual) {
                case 1:
                    printf("Uma alma perdida relata ataques de um Shinigami nas ruas de Karakura.\n");
                    break;
                case 2:
                    printf("Rastros de uma criatura desconhecida marcam a areia de Hueco Mundo.\n");
                    break;
                default:
                    printf("Uma inscricao antiga fala da origem dos tres mundos.\n");
                    break;
            }
            t->casas[t->posicao_player].visitada = 1;
            break;

		case CASA_TESOURO:
			printf("VOCE ACHOU UM TESOURO !\n GANHOU %d XP\n", XP_TESOURO);
			ganhar_xp(p , XP_TESOURO);
			t->casas[t->posicao_player].visitada = 1;
			break;

		case CASA_CURA:{
			int quantidade = p->vida_maxima * 25 / 100;

			if((p->vida_maxima - p->vida_atual) < quantidade){
				quantidade = p->vida_maxima - p->vida_atual;
			}

			curar(p , quantidade);

			if(quantidade == 0){
				printf("VOCE ENCONTROU UMA CURA !\n NAO RECUPERA VIDA POIS SUA VIDA JA ESTA CHEIA \n");
				t->casas[t->posicao_player].visitada = 1;
                break;
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
				printf("\nMISSAO CUMPRIDA! O caminho ate o chefe esta livre!\n");
				printf("press ENTER para continuar\n");
				pausar();
    			t->missao_concluida = 1;
    			t->casas[t->posicao_player].visitada = 1;
    			break;

        case CASA_COMBATE: {
            Monstro monstro;

            int indice = t->casas[t->posicao_player].indice_monstro;

            criar_monstro(&monstro, t->fase_atual, indice);

			ResultadoCombate resultado = combate(p, &monstro);

			if (resultado == RESULTADO_COMBATE_VITORIA) {
   				 t->casas[t->posicao_player].visitada = 1;
			}

            break;
        }

        case CASA_CHEFE: {
            Monstro monstro;

            int indice =
                t->casas[t->posicao_player].indice_monstro;

            criar_monstro(&monstro, t->fase_atual, indice);

			ResultadoCombate resultado = combate(p, &monstro);

			if (resultado == RESULTADO_COMBATE_VITORIA) {
    			t->casas[t->posicao_player].visitada = 1;
			}
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


