#include <stdio.h>

#include "tipos.h"

#include "personagem.h"

int main(){
        printf("bleach echoes of the void \n");
	Personagem personagem;

	criar_personagem(&personagem,0 , "Lucas antonio");

	printf("nome = %s \n", personagem.nome);
	printf("vida atual = %d \n", personagem.vida_atual);
	printf("arma = %s \n ", personagem.arma);
	printf("roupa = %s \n ", personagem.roupa);


        return 0;

}
