#include <string.h>

#include "menu.h"

#include <stdio.h>


void limpar_terminal(void) {
    printf("\033[3J\033[2J\033[H");
    fflush(stdout);
}

void pausar(){
	char descarte[32];
	fgets(descarte, sizeof(descarte), stdin);

}


int ler_inteiro(void) {
    char linha[32];
    int numero;

    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return -1;
    }

    if (sscanf(linha, "%d", &numero) != 1) {
        return -1;
    }

    return numero;
}

ClasseDoPersonagem menu_escolher_classe(void){
	int classe = 4;
	do{

		limpar_terminal();

		printf("BLEACH\n");
		printf("ECHOES OF THE VOID\n");

		printf("\n[1] SHINIGAMI\n");
		printf("Guerreiros da Soul Society. Classe equilibrada,");
		printf(" com boa vida, forca e defesa.\n");
		printf("Vida: 110 | Forca: 11 | Defesa: 9 | Agilidade: 7 | Inteligencia: 7\n");

		printf("\n[2] QUINCY\n");
		printf("Manipuladores de particulas espirituais.");
		printf(" Especialistas em velocidade e inteligencia.\n");
		printf("Vida: 90 | Forca: 7 | Defesa: 6 | Agilidade: 12 | Inteligencia: 10\n");

		printf("\n[3] HOLLOW\n");
		printf("Criaturas espirituais predadoras. Possuem");
		printf(" grande forca fisica, mas pouca defesa.\n");
		printf("Vida: 100 | Forca: 13 | Defesa: 4 | Agilidade: 8 | Inteligencia: 4\n");

		printf("\n");
		printf("\n");
		printf("ESCOLHA A CLASSE DO SEU PERSONAGEM : ");
		classe = ler_inteiro();

		if (classe < 1 || classe > 3){
			printf("\n");
			printf("\n");
			printf("CLASSE INVALIDA ! TENTE NOVAMENTE ! \n");
			printf("press ENTER para continuar");

			pausar();
		}

	}while (classe < 1 || classe > 3);

	return classe - 1;

}

void ler_nome(char nome[], int tamanho){
	do{
		limpar_terminal();
		printf("digite o nome do seu personagem : ");
		fgets(nome , tamanho , stdin);
		nome[strcspn(nome, "\n")] = '\0';

		if(nome[0] == '\0'){
			printf("NOME INVALIDO, DIGITE NOVAMENTE !\n");
			printf("press ENTER para continuar");
			pausar();

		}


	}while(nome[0] == '\0');



}
