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

        return 0;

}
