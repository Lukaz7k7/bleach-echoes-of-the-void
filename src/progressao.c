#include <stdio.h>
#include <stdlib.h>

#include "progressao.h"


int xp_necessario(int nivel){
	return nivel * XP_POR_NIVEL;
}


const char *nome_da_habilidade(ClasseDoPersonagem classe){
	switch (classe){
		case CLASSE_SHINIGAMI:
			return "bankai";

		case CLASSE_QUINCY:
			return "Heilig Pfeil";

		case CLASSE_HOLLOW:
			return "Cero";
	}
	return "Habilidade";
}


int bonus_habilidade(Personagem *p){
	return (p->nivel_habilidade - 1) * BONUS_DANO_HABILIDADE;
}


static void subir_nivel(Personagem *p){
	p->nivel++;

	p->vida_maxima = p->vida_maxima + BONUS_VIDA_NIVEL;
	p->vida_atual = p->vida_atual + BONUS_VIDA_NIVEL;
	p->forca++;
	p->defesa++;
	p->agilidade++;
	p->inteligencia++;

	printf("\n*** VOCE SUBIU PARA O NIVEL %d! ***\n", p->nivel);
	printf("Vida maxima +%d | Forca +1 | Defesa +1 | Agilidade +1 | Inteligencia +1\n",
	       BONUS_VIDA_NIVEL);

	
	if((p->nivel == 3 || p->nivel == 5) && p->nivel_habilidade < NIVEL_HABILIDADE_MAX){
		p->nivel_habilidade++;
		printf("Sua habilidade %s evoluiu para o nivel %d!\n",
		       nome_da_habilidade(p->classe), p->nivel_habilidade);
	}
}


void ganhar_xp(Personagem *p, int xp){
	if(xp <= 0){
		return;
	}

	p->xp = p->xp + xp;

	while(p->xp >= xp_necessario(p->nivel)){
		p->xp = p->xp - xp_necessario(p->nivel);
		subir_nivel(p);
	}
}


void aplicar_bonus_aleatorio(Personagem *p){
	switch(rand() % 5){
		case 0:
			p->forca++;
			printf("BONUS ALEATORIO: Forca +1\n");
			break;

		case 1:
			p->defesa++;
			printf("BONUS ALEATORIO: Defesa +1\n");
			break;

		case 2:
			p->agilidade++;
			printf("BONUS ALEATORIO: Agilidade +1\n");
			break;

		case 3:
			p->inteligencia++;
			printf("BONUS ALEATORIO: Inteligencia +1\n");
			break;

		default:
			p->vida_maxima = p->vida_maxima + BONUS_VIDA_ALEATORIO;
			p->vida_atual = p->vida_atual + BONUS_VIDA_ALEATORIO;
			printf("BONUS ALEATORIO: Vida maxima +%d\n", BONUS_VIDA_ALEATORIO);
			break;
	}
}