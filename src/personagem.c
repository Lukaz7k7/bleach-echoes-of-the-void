#include <string.h>

#include "personagem.h"

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

