#include "monstros.h"

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
