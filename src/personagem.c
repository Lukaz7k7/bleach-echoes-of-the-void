#include <string.h>

#include "personagem.h"

#include <stdio.h>

void criar_personagem(Personagem *p, ClasseDoPersonagem classe, char nome[]) {
	strcpy(p->nome, nome);
	p->classe = classe;
	p->nivel = 1;
	p->xp = 0;
	p->ativa_defesa = 0;
	switch (classe) {
		case CLASSE_SHINIGAMI:
			p->vida_atual = 110;
			p->vida_maxima = 110;
			p->forca = 11;
			p->defesa = 9;
			p->agilidade = 7;
			p->inteligencia = 7;
			strcpy(p->arma, "zanpakuto");
			strcpy(p->roupa, "shihakusho");
			break;

		case CLASSE_QUINCY:
			p->vida_atual = 90;
			p->vida_maxima = 90;
			p->forca = 7;
			p->defesa = 6;
			p->agilidade = 12;
			p->inteligencia = 10;
			strcpy(p->arma, "arco espiritual");
			strcpy(p->roupa, "tunicas quincy");
			break;

		case CLASSE_HOLLOW:
			p->vida_atual = 100;
			p->vida_maxima = 100;
			p->forca = 13;
			p->defesa = 4;
			p->agilidade = 8;
			p->inteligencia = 4;
			strcpy(p->arma, "nenhuma");
			strcpy(p->roupa, "mascara hollow");
			break;
	}
}

const char *nome_da_classe(ClasseDoPersonagem classe){
	switch (classe){
		case CLASSE_SHINIGAMI:
			return "Shinigami";

		case CLASSE_QUINCY:
			return "Quincy";

		case CLASSE_HOLLOW:
			return "Hollow";
	}
	return "desconhecida";

}



void mostrar_personagem(Personagem *p) {

    printf("\n");
    printf("  +------------------------------------------------------+\n");
    printf("  |                  STATUS DO PERSONAGEM                 \n");
    printf("  +------------------------------------------------------+\n");

    printf("  | NOME: %-20s CLASSE: %-14s \n",
           p->nome, nome_da_classe(p->classe));

    printf("  +------------------------------------------------------+\n");
    printf("  | VIDA: %d/%d                                      \n",
           p->vida_atual, p->vida_maxima);

    printf("  | NIVEL: %-4d XP: %-10d                       \n",
           p->nivel, p->xp);

    printf("  +------------------------------------------------------+\n");
    printf("  |                     ATRIBUTOS                        \n");

    printf("  | FORCA: %-4d DEFESA: %-4d AGILIDADE: %-4d      \n",
           p->forca, p->defesa, p->agilidade);

    printf("  | INTELIGENCIA: %-5d                                \n",
           p->inteligencia);

    printf("  +------------------------------------------------------+\n");
    printf("  |                    EQUIPAMENTOS                      \n");

    printf("  | ARMA: %-47s \n", p->arma);
    printf("  | ROUPA: %-46s \n", p->roupa);

    printf("  +------------------------------------------------------+\n");
    printf("\n");
}














