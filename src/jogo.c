#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

int rolar_dado(int lados){

	return rand() % lados + 1;

}
