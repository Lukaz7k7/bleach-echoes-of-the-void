#include <stdio.h>

#include "combate.h"
#include "jogo.h"
#include "personagem.h"
#include "menu.h"

/* Imprime uma barra visual de vida */
static void mostrar_barra_vida(
	const char *nome,
    int vida,
    int vida_maxima,
    const char *cor
) {
    int largura = 24;
    int preenchida = 0;

    if (vida_maxima > 0) {

        int vida_segura = vida;

        if (vida_segura < 0) {
            vida_segura = 0;
        }

        if (vida_segura > vida_maxima) {
            vida_segura = vida_maxima;
        }

        preenchida = vida_segura * largura / vida_maxima;
    }

    printf("%s%-16s\033[0m [", cor, nome);

    for (int i = 0; i < largura; i++) {

        if (i < preenchida) {
            printf("#");
        } else {
            printf("-");
        }
    }

    printf("] %d/%d\n", vida, vida_maxima);
}


/* Tela apresentada quando o combate comeca */
void mostrar_inicio_combate(Personagem *p, Monstro *m) {

    limpar_terminal();

    printf("\n");
    printf("============================================================\n");
    printf("                  COMBATE INICIADO!\n");
    printf("============================================================\n\n");

    printf("\033[1;31m");
    printf("                    %s\n", m->nome);
    printf("\033[0m\n");

    printf("%s\n\n", m->descricao);

    printf("JOGADOR: %s (%s)\n",
           p->nome, nome_da_classe(p->classe));

    mostrar_barra_vida(
        "VIDA",
        p->vida_atual,
        p->vida_maxima,
        "\033[1;36m"
    );

    printf("\n");

    printf("INIMIGO: %s\n", m->nome);

    mostrar_barra_vida(
        "VIDA",
        m->vida_atual,
        m->vida_maxima,
        "\033[1;31m"
    );

    printf("\n");
    printf("============================================================\n");
    printf("                 PREPARE-SE PARA LUTAR!\n");
    printf("============================================================\n");

    printf("\nPressione ENTER para continuar...");

    pausar();
}


/* Tela apresentada durante o turno do jogador */
void mostrar_turno_jogador(
    Personagem *p,
    Monstro *m,
    int habilidade_usada
) {

    limpar_terminal();

    printf("\n");
    printf("============================================================\n");
    printf("                  TURNO DO JOGADOR\n");
    printf("============================================================\n\n");

    printf("\033[1;36m");
    printf("JOGADOR: %s (%s)\n",
           p->nome, nome_da_classe(p->classe));
    printf("\033[0m");

    mostrar_barra_vida(
        "VIDA",
        p->vida_atual,
        p->vida_maxima,
        "\033[1;36m"
    );

    printf("\n");

    printf("\033[1;31m");
    printf("INIMIGO: %s\n", m->nome);
    printf("\033[0m");

    mostrar_barra_vida(
        "VIDA",
        m->vida_atual,
        m->vida_maxima,
        "\033[1;31m"
    );

    printf("\n");
    printf("============================================================\n");
    printf("                  ESCOLHA SUA ACAO\n");
    printf("============================================================\n\n");

    printf("[1] ATACAR\n");
    printf("[2] DEFENDER\n");

    if (habilidade_usada == 0) {
        printf("[3] HABILIDADE ESPECIAL [DISPONIVEL]\n");
    } else {
        printf("[3] HABILIDADE ESPECIAL [UTILIZADA]\n");
    }

    printf("[4] FUGIR\n");

    printf("\nSua escolha: ");
}


int atributo_principal(Personagem *p){
	switch(p->classe){

		case CLASSE_SHINIGAMI:
			return p->forca;
		case CLASSE_HOLLOW:
			return p->forca;
		case CLASSE_QUINCY:
			return p->agilidade;
	}
	return 0;
}


int calcula_dano(int ataque , int defesa){
	int dano = ataque - defesa;

	if(dano < 1){
		dano = 1;
	}

	return dano;

}


static int turno_monstro(Monstro *m, Personagem *p){
	int ataque = 0;
	if(p->ativa_defesa == 1){
		ataque = (rolar_dado(DADO_COMBATE) + m->ataque) - (p->defesa * 2);
		p->ativa_defesa = 0;
	}
	else{
		ataque = (rolar_dado(DADO_COMBATE) + m->ataque) - p->defesa;
	}

	return ataque;
}

static int turno_player(Personagem *p, Monstro *m, int *habilidade_usada){

	int opcao;
    int ataque;
    int dano;
    int dado;

	mostrar_turno_jogador(p, m, *habilidade_usada);
	opcao = ler_inteiro();

	while((opcao < ACAO_ATACAR ) || (opcao > ACAO_FUGIR) || ((opcao == ACAO_FUGIR) && (m->chefe == 1)) || ((opcao == ACAO_HABILIDADE) && (*habilidade_usada == 1))){
		mostrar_turno_jogador(p, m, *habilidade_usada);
		printf("OPCAO INVALIDA ! TENTE NOVAMENTE !\n");
		if((opcao == ACAO_FUGIR) && (m->chefe == 1)){
			printf("NÃO PODE FUGIR NA BATALHA DO CHEFE!\n");
		}
		if((opcao == ACAO_HABILIDADE) && (*habilidade_usada == 1)){
			printf("A HABILIDADE ESPECIAL ESTA INDISPONIVEL NO MOMENTO !\n");
		}
		opcao = ler_inteiro();
	}
	
	dado = rolar_dado(DADO_COMBATE);

	switch(opcao){
		case ACAO_ATACAR:
			ataque = (atributo_principal(p) + dado) - m->defesa;
			dano = calcula_dano(ataque, m->defesa );
			dano_monstro(m,dano);

			printf("\nVoce atacou %s!\n", m->nome);
            printf("Dado: %d\n", dado);
            printf("Dano causado: %d\n", dano);
            printf("Vida do inimigo: %d/%d\n",
                   m->vida_atual, m->vida_maxima);

			break;

		case ACAO_DEFENDER:
				p->ativa_defesa = 1;

				printf("\nVoce assumiu uma postura defensiva!\n");
	            printf("Sua defesa sera aumentada no proximo ataque inimigo.\n");
				break;

		case ACAO_HABILIDADE:
			*habilidade_usada = 1;

            dado = rolar_dado(DADO_COMBATE);

            ataque = atributo_principal(p) + dado + 5;

            dano = calcula_dano(ataque, m->defesa);

            dano_monstro(m, dano);

            printf("\nVOCE UTILIZOU SUA HABILIDADE ESPECIAL!\n");
            printf("Dado: %d\n", dado);
            printf("Dano causado: %d\n", dano);
            printf("Vida do inimigo: %d/%d\n",
                   m->vida_atual, m->vida_maxima);

            break;
			
		case ACAO_FUGIR:
			printf("\nVoce fugiu do combate!\n");
            return 1;
	}

	return 0;


}
