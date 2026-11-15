#ifndef TIPOS_H

#define TIPOS_H

#define TAM_TABULEIRO 12

#define INDICE_MISSAO 8

#define DADO_MOVIMENTACAO 6

#define DADO_COMBATE 20

#define VALOR_FUGA 20

#define XP_TESOURO 50

#define XP_POR_NIVEL 100 
        
#define BONUS_VIDA_NIVEL 10       

#define BONUS_VIDA_ALEATORIO 5   

#define NIVEL_HABILIDADE_MAX 3   

#define BONUS_DANO_HABILIDADE 3   

typedef enum{
	CLASSE_SHINIGAMI,
	CLASSE_QUINCY,
	CLASSE_HOLLOW
} ClasseDoPersonagem;

typedef enum{
	RESULTADO_FASE_CONCLUIDA,
	RESULTADO_FASE_DERROTA
} ResultadoFase;

typedef enum{
	RESULTADO_COMBATE_VITORIA,
	RESULTADO_COMBATE_DERROTA,
	RESULTADO_COMBATE_FUGA
} ResultadoCombate;

typedef enum{
	CASA_VAZIA,
	CASA_COMBATE,
	CASA_TESOURO,
	CASA_CURA,
	CASA_ARMADILHA,
	CASA_MISSAO,
	CASA_CHEFE
} TipoDeCasa;

typedef enum{
	ACAO_ATACAR = 1,
	ACAO_DEFENDER,
	ACAO_HABILIDADE,
	ACAO_FUGIR
} AcaoCombate;

typedef struct {
	char nome[50];
	ClasseDoPersonagem classe;
	int vida_atual;
	int vida_maxima;
	int forca;
	int defesa;
	int ativa_defesa;
	int agilidade;
	int inteligencia;
	int xp;          /* xp rumo ao proximo nivel */
	int nivel;
	int nivel_habilidade;
	char arma[50];
	char roupa[50];
} Personagem;

typedef struct {
	char nome[50];
	char descricao[100];
	int vida_atual;
	int vida_maxima;
	int ataque;
	int defesa;
	int nivel;
	int xp_recompensa;
	int chefe; /* se for chefe = 1 */
} Monstro;

typedef struct {
	int visitada;
	TipoDeCasa evento;
	int indice_monstro;  /* indice do monstro na fase, -1 = nenhum */
} Casa;

typedef struct {
	Casa casas[TAM_TABULEIRO];
	int posicao_player;
	int fase_atual;
	int missao_concluida; /* 1 = missao da fase cumprida */
} Tabuleiro;

#endif



