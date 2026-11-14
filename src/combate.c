#include "monstros.h"
#include "combate.h"
#include "jogo.h"

int atributo_principal(Personagem *p){
	switch(p->classe){

		case CLASSE_SHINIGAMI:
			return p->forca;
		case CLASSE_HOLLOW:
			return p->forca;
		case CLASSE_QUINCY:
			return p->agilidade;
	}
	return 0;
}


int calcula_dano(int ataque , int defesa){
	int dano = ataque - defesa;

	if(dano < 1){
		dano = 1;
	}

	return dano;

}


static int turno_monstro(Monstro *m, Personagem *p){
	int ataque = 0;
	if(p->ativa_defesa == 1){
		ataque = (rolar_dado(DADO_COMBATE) + m->ataque) - (p->defesa * 2);
		p->ativa_defesa = 0;
	}
	else{
		ataque = (rolar_dado(DADO_COMBATE) + m->ataque) - p->defesa;
	}

	return ataque;
}
