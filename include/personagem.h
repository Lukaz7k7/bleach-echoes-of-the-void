#ifndef PERSONAGEM_H

#define PERSONAGEM_H

#include "tipos.h"

void criar_personagem(Personagem *p, ClasseDoPersonagem classe, char nome[]);

void mostrar_personagem(Personagem *p);

const char *nome_da_classe(ClasseDoPersonagem classe);

#endif
