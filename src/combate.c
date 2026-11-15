#include <stdio.h>
#include "monstros.h"
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


static int turno_monstro(Monstro *m, Personagem *p) {

    int dado;
    int ataque;
    int dano;
    int defesa_usada;

    dado = rolar_dado(DADO_COMBATE);
    ataque = dado + m->ataque;

    
    if (p->ativa_defesa == 1) {

        defesa_usada = p->defesa * 2;


        p->ativa_defesa = 0;
    }
    else {
        defesa_usada = p->defesa;
    }

    
    dano = calcula_dano(ataque, defesa_usada);

    limpar_terminal();
    printf("\n");
    printf("============================================================\n");
    printf("                   TURNO DO MONSTRO\n");
    printf("============================================================\n\n");

    printf("%s ATACOU!\n\n", m->nome);

    printf("DADO ROLADO:          %d\n", dado);
    printf("ATAQUE DO MONSTRO:    %d\n", m->ataque);
    printf("ATAQUE TOTAL (ataque + dado):         %d\n", ataque);

    printf("\n");
    printf("SUA DEFESA:           %d\n", defesa_usada);
    printf("DANO RECEBIDO:        %d\n", dano);

    receber_dano(p, dano);

    printf("\n");
    printf("VIDA RESTANTE:        %d/%d\n",
           p->vida_atual, p->vida_maxima);

    printf("\n============================================================\n");
	printf("press ENTER para continuar...");
	pausar();


    return dano;
}

static int turno_player(Personagem *p, Monstro *m, int *habilidade_usada) {

    int opcao;
    int ataque;
    int dano;
    int dado;

    mostrar_turno_jogador(p, m, *habilidade_usada);

    printf("\nSua escolha: ");
    opcao = ler_inteiro();

    while (
        (opcao < ACAO_ATACAR) ||
        (opcao > ACAO_FUGIR) ||
        ((opcao == ACAO_FUGIR) && (m->chefe == 1)) ||
        ((opcao == ACAO_HABILIDADE) && (*habilidade_usada == 1))
    ) {

        printf("\nOPCAO INVALIDA! TENTE NOVAMENTE!\n");

        if ((opcao == ACAO_FUGIR) && (m->chefe == 1)) {
            printf("NAO PODE FUGIR NA BATALHA DO CHEFE!\n");
        }

        if ((opcao == ACAO_HABILIDADE) && (*habilidade_usada == 1)) {
            printf("A HABILIDADE ESPECIAL ESTA INDISPONIVEL!\n");
        }

        printf("\nSua escolha: ");
        opcao = ler_inteiro();
    }

    switch (opcao) {

        case ACAO_ATACAR:

            dado = rolar_dado(DADO_COMBATE);

            ataque = atributo_principal(p) + dado;

            dano = calcula_dano(ataque, m->defesa);

            dano_monstro(m, dano);

			limpar_terminal();
            printf("\nVoce atacou %s!\n", m->nome);
            printf("Dado: %d\n", dado);
            printf("Ataque total (dado + atributo principal ): %d\n", ataque);
            printf("Dano causado ( ataque - defesa do inimigo ): %d\n", dano);
            printf("Vida do inimigo: %d/%d\n",
                   m->vida_atual, m->vida_maxima);
			printf("press ENTER para continuar..");
			pausar();
            break;

        case ACAO_DEFENDER:

            p->ativa_defesa = 1;
			
			limpar_terminal();
			printf("\nVOCE ESTA EM POSICAO DEFENSIVA!\n");
			printf("Sua defesa foi dobrada!\n");

			printf("press ENTER para continuar...");
			pausar();
            break;

        case ACAO_HABILIDADE:

            *habilidade_usada = 1;

            dado = rolar_dado(DADO_COMBATE);

            ataque = atributo_principal(p) + dado + 5;

            dano = calcula_dano(ataque, m->defesa);

            dano_monstro(m, dano);
			
			limpar_terminal();
            printf("\nVOCE UTILIZOU SUA HABILIDADE ESPECIAL!\n");
            printf("Dado: %d\n", dado);
            printf("Ataque total: %d\n", ataque);
            printf("Dano causado: %d\n", dano);
            printf("Vida do inimigo: %d/%d\n",
                   m->vida_atual, m->vida_maxima);
			printf("press ENTER para continuar...");
			pausar();

            break;

        case ACAO_FUGIR:
			dado = rolar_dado(DADO_COMBATE);
			limpar_terminal();
			printf("\nVoce tentou fugir de %s!\n", m->nome);
            printf("Dado: %d\n", dado);
            printf("total: %d\n", (dado+p->agilidade));

			if((dado + p->agilidade) >= VALOR_FUGA){
            printf("\nVoce conseguiu fugir do combate!\n");
            return 1;	
			}
			else {
			printf("sua fuga falhou !\n");
			printf("voce precisa de %d para fugir \n", VALOR_FUGA);
			printf("press ENTER para continuar...");
			pausar();
			}
    }

    return 0;
}

ResultadoCombate combate(Personagem *p , Monstro *m){
	mostrar_inicio_combate(p,m);
	int habilidade_usada = 0;
	int fugiu = 0;

	while((p->vida_atual > 0 ) && (m->vida_atual > 0)){
		fugiu = turno_player(p, m, &habilidade_usada);
	
		if(fugiu == 1){
			return RESULTADO_COMBATE_FUGA;
		}

		if(m->vida_atual < 1){
			break;
		}


		turno_monstro(m , p);

		if(p->vida_atual < 1){
			break;
		}

	}

	if(p->vida_atual < 1 ){

	}

	if (m->vida_atual <= 0) {

		limpar_terminal();
        printf("\n");
        printf("============================================================\n");
        printf("                  VITORIA NO COMBATE!\n");
        printf("============================================================\n");

        printf("\nVoce derrotou %s!\n", m->nome);
        printf("XP recebido: %d\n", m->xp_recompensa);

        ganhar_xp(p, m->xp_recompensa);

        printf("XP total: %d\n", p->xp);

        printf("\nPressione ENTER para continuar...");
        pausar();

        return RESULTADO_COMBATE_VITORIA;
    }

    
    if (p->vida_atual <= 0) {

		limpar_terminal();
        printf("\n");
        printf("============================================================\n");
        printf("                   VOCE FOI DERROTADO!\n");
        printf("============================================================\n");

        printf("\n%s venceu o combate!\n", m->nome);
		printf("\n");
		mostrar_personagem(p);
        printf("\nPressione ENTER para continuar...");
        pausar();

        return RESULTADO_COMBATE_DERROTA;
    }

    return RESULTADO_COMBATE_DERROTA;
}


