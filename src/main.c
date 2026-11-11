#include <stdio.h>

#include "tipos.h"

#include "personagem.h"

#include "menu.h"

int main(){
	Personagem personagem;

	ClasseDoPersonagem classe = menu_escolher_classe();

	criar_personagem(&personagem,classe , "Lucas antonio");

	mostrar_personagem(&personagem);

        return 0;

}
