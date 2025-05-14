#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <stdbool.h>


#define CELULA 64
#define ALTURA 15
#define LARGURA 15

typedef struct {
    bool vida;
    int velocidade;
    int x, y;
    int tamanho;
    Color cor;
    double ultimoMovimento;
    double cooldownCaminhar;
    int cooldownbomba;
    int bombas;
} Jogador;

void CriarPersonagem(Jogador *p);

void AtualizarPersonagem(Jogador *p, int mapa[ALTURA][LARGURA]);

void DesenharPersonagem(Jogador p);

#endif
