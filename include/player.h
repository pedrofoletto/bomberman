#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <stdbool.h>

#define MAX_BOMBAS 10
#define CELULA 64
#define ALTURA 15
#define LARGURA 15

typedef enum direction { NORTE = 0, LESTE, SUL, OESTE} direction;

typedef enum {
    BOMB_STATE_TICKING,
    BOMB_STATE_EXPLODING,
    BOMB_STATE_INACTIVE
} BombaState;

typedef struct {
    BombaState state; // O estado atual da bomba
    double time; 
    int x, y;
    int range;
    
    //alcance explosao 
    int reachUp, reachDown, reachLeft, reachRight;

    // Animação da bomba
    int frameAtual;
    double tempoFrame;
    double tempoUltimoFrame;

    // Animação da explosão
    double tempoVisivelExplosao; // Quanto tempo a explosão fica na tela
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
    int score;
    int alcance;
    int bombas_colocadas;
    //fru fru de animação
    direction direcao;
    int frameAtual;
    double tempoFrame;
    double tempoUltimoFrame;
    //
    Bomba listaBombas[MAX_BOMBAS];
} Jogador;

void CriarPersonagem(Jogador *p);

int AtualizarPersonagem(Jogador *p, int mapa[ALTURA][LARGURA]);

void DesenharPersonagem(Jogador p,Texture2D sheet);

#endif
