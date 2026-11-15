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

	for (int i = 1; i < 4; i++) {

    
		int vida_anterior = personagem.vida_atual;

		curar(&personagem, personagem.vida_maxima);

		int vida_recuperada = personagem.vida_atual - vida_anterior;

		if (i > 1) {
			limpar_terminal();

			printf("\n");
			printf("============================================================\n");
			printf("                   NOVA FASE!\n");
			printf("============================================================\n\n");

			printf("Voce se preparou para continuar sua jornada.\n");
			printf("Vida recuperada: %d HP\n", vida_recuperada);
			printf("Vida atual: %d/%d HP\n",
				personagem.vida_atual, personagem.vida_maxima);

			printf("\nPressione ENTER para continuar...");
			pausar();
		}

		montar_tabuleiro(&tab, i);

		ResultadoFase fase = jogar_fase(&personagem, &tab);

		if (fase == RESULTADO_FASE_DERROTA) {
			limpar_terminal();
			mostrar_tela_game_over(&personagem);
			return 0;
		}
    }

	mostrar_tela_vitoria(&personagem);
	return 0;
}