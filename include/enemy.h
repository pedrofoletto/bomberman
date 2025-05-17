#ifndef ENEMY_H
#define ENEMY_H
#include <raylib.h>
#include <stdbool.h>
#include "player.h"
#include "stdlib.h"

#define MAX_BOMBAS 1
#define CELULA 64
#define ALTURA 15
#define LARGURA 15
#define DETECCAO 128


typedef struct {
    bool vida;
    int velocidade;
    int x, y;
    int tamanho;
    double ultimoMovimento;
    double cooldownCaminhar;
    //fru fru de animação
    direction direcao;
    int frameAtual;
    double tempoFrame;
    double tempoUltimoFrame;
    //
} Inimigo;

void CriarInimigo(Inimigo *p);

void AtualizarInimigo(Inimigo *p, int mapa[ALTURA][LARGURA],Jogador *j);

void DesenharInimigo(Inimigo p);

#endif
