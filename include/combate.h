#ifndef COMBATE_H
#define COMBATE_H

#include "tipos.h"

void mostrar_inicio_combate(Personagem *p, Monstro *m);

void mostrar_turno_jogador(
    Personagem *p,
    Monstro *m,
    int habilidade_usada
);

int atributo_principal(Personagem *p);

int calcula_dano(int ataque, int defesa);

ResultadoCombate combate(Personagem *p, Monstro *m);

#endif
