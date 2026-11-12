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

	for(int i = 0; i < 8; i++){

		limpar_terminal();

		mostrar_personagem(&personagem);
		mostrar_tabuleiro(&tab);

		printf("press ENTER para rolar o dado\n");

		pausar();

		int passos = rolar_dado(DADO_MOVIMENTACAO);

		mover_personagem(&tab, passos);

		limpar_terminal();

		printf("VOCE TIROU --> %d <-- NO DADO\n", passos);

		executar_evento(&personagem, &tab);

                printf("\nPressione ENTER para continuar...\n");
                pausar();

		if(personagem.vida_atual <= 0){
			limpar_terminal();
			printf("VOCE MORREU ! FIM DA JORNADA !\n");
			break;
		}
	}

        return 0;

}
