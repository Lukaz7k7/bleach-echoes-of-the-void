#include <stdio.h>

#include "tipos.h"

#include "personagem.h"

#include "menu.h"

int main(){
	char nome[100];

	Personagem personagem;

	ClasseDoPersonagem classe = menu_escolher_classe();

	ler_nome(nome, 32);

	criar_personagem(&personagem,classe , nome);

	mostrar_personagem(&personagem);

        return 0;

}
