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

	mostrar_personagem(&personagem);

	Tabuleiro tab;

	montar_tabuleiro(&tab , 1);

	mostrar_tabuleiro(&tab);

	tab.missao_concluida = 1;

	for(int i = 0; i < 8; i++){
		int passos = 0;

		printf("press ENTER para rolar o dado\n");
		char descarte[32];
		fgets(descarte, sizeof(descarte), stdin);

		passos = rolar_dado(DADO_MOVIMENTACAO);

		limpar_terminal();

		printf("VOCE TIROU --> %d <-- NO DADO\n", passos);
		printf("press ENTER para andar no tabuleiro\n");

                fgets(descarte, sizeof(descarte), stdin);

		limpar_terminal();

                mover_personagem(&tab, passos );
		mostrar_personagem(&personagem);
		mostrar_tabuleiro(&tab);

	}

        return 0;

}
