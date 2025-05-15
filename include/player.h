#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <stdbool.h>

#define MAX_BOMBAS 1
#define CELULA 64
#define ALTURA 15
#define LARGURA 15

typedef struct {
    int time;
    int x, y;
    int tick;
    int range;
    bool ativa;
    int tempo_explosao;
    bool explodiu;
    double inicioExplosao;
} Bomba;

typedef struct {
    bool vida;
    int velocidade;
    int x, y;
    int tamanho;
    Color cor;
    double cooldown;
    double ultimoMovimento;
    double cooldownCaminhar;
    int cooldownbomba;
    int bombas;
    Bomba listaBombas[MAX_BOMBAS];
} Jogador;

void CriarPersonagem(Jogador *p);

void AtualizarPersonagem(Jogador *p, int mapa[ALTURA][LARGURA]);

void DesenharPersonagem(Jogador p);

#endif
