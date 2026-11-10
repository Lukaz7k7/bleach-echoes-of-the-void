#ifndef TIPOS_H
#define TIPOS_H

typedef enum{
	CLASSE_SHINIGAMI,
	CLASSE_QUINCY,
	CLASSE_HOLLOW
} ClasseDoPersonagem;

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
	ClasseDoPersonagem classe ;
	int vida_atual;
	int vida_maxima;
	int forca;
	int defesa;
	int ativa_defesa;
	int agilidade;
	int inteligencia;
	int xp;
	int nivel;
	char arma[50];
} Personagem;

#endif
