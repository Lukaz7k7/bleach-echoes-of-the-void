#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "tipos.h"

void definir_casa(Casa *c, TipoDeCasa tipo, int indice_monstro);

void montar_tabuleiro(Tabuleiro *t, int fase);

void mostrar_tabuleiro(Tabuleiro *t);

#endif
