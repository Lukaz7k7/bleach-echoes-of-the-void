#ifndef PROGRESSAO_H
#define PROGRESSAO_H

#include "tipos.h"

int xp_necessario(int nivel);

void ganhar_xp(Personagem *p, int xp);

void aplicar_bonus_aleatorio(Personagem *p);

const char *nome_da_habilidade(ClasseDoPersonagem classe);

int bonus_habilidade(Personagem *p);

#endif