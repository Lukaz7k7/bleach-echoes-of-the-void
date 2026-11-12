#ifndef JOGO_H
#define JOGO_H

#include "tipos.h"

int rolar_dado(int lados);

void executar_evento(Personagem *p, Tabuleiro *t);

ResultadoFase jogar_fase(Personagem *p, Tabuleiro *t);

#endif
