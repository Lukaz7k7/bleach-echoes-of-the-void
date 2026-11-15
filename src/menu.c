#include <string.h>

#include "menu.h"

#include <stdio.h>

#include <time.h>

void limpar_terminal(void) {
    printf("\033[3J\033[2J\033[H");
    fflush(stdout);
}

void pausar(){
	char descarte[32];
	fgets(descarte, sizeof(descarte), stdin);

}

void esperar(double segundos){
    clock_t fim = clock() + (clock_t)(segundos * CLOCKS_PER_SEC);
    fflush(stdout);
    while (clock() < fim) { }
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


ClasseDoPersonagem menu_escolher_classe(void) {

    int classe = 4;

    do {

        limpar_terminal();

        printf("\n");
        printf("============================================================\n");
        printf("                 BLEACH: ECHOES OF THE VOID\n");
        printf("                    ESCOLHA SUA CLASSE\n");
        printf("============================================================\n");

        /* SHINIGAMI */
        printf("\n");
        printf("\033[1;36m");
        printf("[1] SHINIGAMI\n");
        printf("\033[0m");

        printf("Guerreiros da Soul Society, especialistas no uso de\n");
        printf("suas Zanpakutos e tecnicas de combate.\n\n");

        printf("ATRIBUTOS INICIAIS:\n");
        printf("Vida: 110 | Forca: 11 | Defesa: 9\n");
        printf("Agilidade: 7 | Inteligencia: 7\n");
        printf("Atributo principal: FORCA\n\n");

        printf("HABILIDADE ESPECIAL: BANKAI\n");
        printf("Libera o poder da Zanpakuto e causa DANO DOBRADO.\n");
        printf("Ideal para jogadores que priorizam forca e ataques\n");
        printf("de alto impacto.\n");

        printf("\n------------------------------------------------------------\n");

        /* QUINCY */
        printf("\n");
        printf("\033[1;34m");
        printf("[2] QUINCY\n");
        printf("\033[0m");

        printf("Manipuladores de Reishi, especialistas em velocidade,\n");
        printf("precisao e ataques com armas espirituais.\n\n");

        printf("ATRIBUTOS INICIAIS:\n");
        printf("Vida: 90 | Forca: 7 | Defesa: 6\n");
        printf("Agilidade: 12 | Inteligencia: 10\n");
        printf("Atributo principal: AGILIDADE\n\n");

        printf("HABILIDADE ESPECIAL: HEILIG PFEIL\n");
        printf("Dispara uma flecha espiritual com precisao aprimorada.\n");
        printf("Rola dois D20 e utiliza o maior resultado.\n");
        printf("Ideal para jogadores que priorizam velocidade.\n");

        printf("\n------------------------------------------------------------\n");

        /* HOLLOW */
        printf("\n");
        printf("\033[1;31m");
        printf("[3] HOLLOW\n");
        printf("\033[0m");

        printf("Criaturas espirituais predadoras, movidas por instintos\n");
        printf("e grande poder ofensivo.\n\n");

        printf("ATRIBUTOS INICIAIS:\n");
        printf("Vida: 100 | Forca: 13 | Defesa: 4\n");
        printf("Agilidade: 8 | Inteligencia: 4\n");
        printf("Atributo principal: FORCA\n\n");

        printf("HABILIDADE ESPECIAL: CERO\n");
        printf("Concentra energia espiritual e dispara uma poderosa\n");
        printf("rajada que IGNORA A DEFESA DO INIMIGO.\n");
        printf("Ideal para jogadores que priorizam forca bruta.\n");

        printf("\n============================================================\n");
        printf("ESCOLHA A CLASSE DO SEU PERSONAGEM: ");

        classe = ler_inteiro();

        if (classe < 1 || classe > 3) {

            printf("\nCLASSE INVALIDA! TENTE NOVAMENTE!\n");
            printf("Pressione ENTER para continuar...");

            pausar();
        }

    } while (classe < 1 || classe > 3);

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
