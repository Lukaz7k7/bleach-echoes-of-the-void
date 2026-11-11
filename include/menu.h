#ifndef MENU_H

#define MENU_H

#include "tipos.h"

void limpar_terminal(void);

ClasseDoPersonagem menu_escolher_classe(void);

int ler_inteiro(void);

void ler_nome(char nome[], int tamanho);

#endif
