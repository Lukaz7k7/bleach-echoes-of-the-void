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
