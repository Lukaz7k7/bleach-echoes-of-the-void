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

	for(int i = 1; i < 4; i++){
		montar_tabuleiro(&tab , i);

		ResultadoFase fase = jogar_fase(&personagem,&tab);

		if(fase == RESULTADO_FASE_DERROTA){
			limpar_terminal();
			printf("GAME OVER\nFIM DA JORNADA,VOCE FOI DERROTADO");
			return 0;
		}
	}

        return 0;

}

