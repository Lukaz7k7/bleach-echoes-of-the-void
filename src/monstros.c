#include <stdio.h>
#include <math.h>
#include "monstros.h"

void criar_monstro(Monstro *m, int fase, int indice) {

    if (m == NULL || fase < 1 || fase > 3 ||
        indice < 0 || indice > 3) {
        return;
    }

    const char *nomes[3][4] = {
        {
            "Hollow Errante",
            "Shinigami Corrompido",
            "Hollow Corrompido",
            "Ceifador Ressonante"
        },
        {
            "Hollow das Dunas",
            "Arrancar Corrompido",
            "Predador de Hueco Mundo",
            "Guardiao da Fenda"
        },
        {
            "Alma Fragmentada",
            "Guardiao das Ruinas",
            "Sentinela do Vale",
            "Aparicion"
        }
    };

    const char *descricoes[3][4] = {
        {
            "Hollow errante que perdeu o controle dos instintos.",
            "Shinigami dominado por uma energia desconhecida.",
            "Hollow alterado pela energia que corrompe Karakura.",
            "Shinigami cuja Zanpakuto absorve energia espiritual."
        },
        {
            "Hollow que percorre as dunas em busca de energia.",
            "Arrancar cuja consciencia foi alterada pela anomalia.",
            "Criatura poderosa que domina Hueco Mundo.",
            "Criatura que protege a passagem para o Vale dos Gritos."
        },
        {
            "Alma presa entre os fragmentos do Vale dos Gritos.",
            "Criatura antiga que protege as ruinas esquecidas.",
            "Ser formado pela energia acumulada neste vale.",
            "Entidade antiga que pretende destruir os tres mundos."
        }
    };

    const int vidas_base[4] = {30, 35, 45, 70};
    const int ataques_base[4] = {6, 8, 10, 11};
    const int defesas_base[4] = {3, 4, 5, 7};

    const double multiplicadores[3] = {1.0, 1.2, 1.4};

    const int xp_base[4] = {25, 35, 50, 100};

    double fator = multiplicadores[fase - 1];

    snprintf(m->nome, sizeof(m->nome), "%s",
             nomes[fase - 1][indice]);

    snprintf(m->descricao, sizeof(m->descricao), "%s",
             descricoes[fase - 1][indice]);

    m->vida_maxima = (int)ceil(vidas_base[indice] * fator);
    m->ataque = (int)ceil(ataques_base[indice] * fator);
    m->defesa = (int)ceil(defesas_base[indice] * fator);

    m->vida_atual = m->vida_maxima;
    m->nivel = fase;
    m->xp_recompensa = xp_base[indice] * fase;

    if(indice == 3){
	m->chefe = 1;
    }

    else {
	m->chefe = 0;
    }

}
