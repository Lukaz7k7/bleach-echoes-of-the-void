#include <stdio.h>

#include "tipos.h"

#include "personagem.h"

#include "menu.h"

#include <stdlib.h>

#include <time.h>

#include "jogo.h"

#include "tabuleiro.h"

int main(){
	srand(time(NULL));

	char nome[32];

	Personagem personagem;

	ClasseDoPersonagem classe = menu_escolher_classe();

	ler_nome(nome, sizeof(nome));

	criar_personagem(&personagem,classe , nome);

	Tabuleiro tab;

	montar_tabuleiro(&tab , 1);

	ResultadoFase fase_1 = jogar_fase(&personagem,&tab);

	if(fase_1 == RESULTADO_FASE_DERROTA){
		limpar_terminal();
		printf("GAMER OUVER\nFIM DA JORNADA,VOCE FOI DERROTADO");
		return 0;
	}

	montar_tabuleiro(&tab,2);

	ResultadoFase fase_2 = jogar_fase(&personagem,&tab);

	if(fase_2 == RESULTADO_FASE_DERROTA){
                limpar_terminal();
                printf("GAMER OUVER\nFIM DA JORNADA,VOCE FOI DERROTADO");
                return 0;
        }

        montar_tabuleiro(&tab,3);

        ResultadoFase fase_3 = jogar_fase(&personagem,&tab);

        if(fase_3 == RESULTADO_FASE_DERROTA){
                limpar_terminal();
                printf("GAMER OUVER\nFIM DA JORNADA,VOCE FOI DERROTADO");
                return 0;
        }

        return 0;

}

