#ifndef MENU_H

#define MENU_H

#include "tipos.h"

void limpar_terminal(void);

void pausar(void);

void esperar(double segundos);

void mostrar_tela_vitoria(Personagem *p);

void mostrar_tela_game_over(Personagem *p);

ClasseDoPersonagem menu_escolher_classe(void);

int ler_inteiro(void);

void ler_nome(char nome[], int tamanho);

#endif
