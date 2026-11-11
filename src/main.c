#include <stdio.h>

#include "tipos.h"

#include "personagem.h"

int main(){
        printf("bleach echoes of the void \n");
	Personagem personagem;

	criar_personagem(&personagem,0 , "Lucas antonio");

	mostrar_personagem(&personagem);

        return 0;

}
