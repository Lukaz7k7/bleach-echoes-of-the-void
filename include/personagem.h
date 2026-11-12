#ifndef PERSONAGEM_H

#define PERSONAGEM_H

#include "tipos.h"

void criar_personagem(Personagem *p, ClasseDoPersonagem classe, char nome[]);

void mostrar_personagem(Personagem *p);

const char *nome_da_classe(ClasseDoPersonagem classe);

void receber_dano(Personagem *p, int dano);

void curar(Personagem *p, int cura);

void ganhar_xp(Personagem *p, int xp);

#endif
