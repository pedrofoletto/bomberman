#include "player.h"

void CriarPersonagem(Jogador *p) {
    p->vida = true;
    p->velocidade = 64;
    p->x = 64;
    p->y = 64;
    p->bombas = 1;
    p->cooldownbomba = 0;
    p->tamanho = 64;
    p->cor = RED;
    p->cooldown = 0.375; //ms
    p->ultimoMovimento = 0.0;
}


void AtualizarPersonagem(Jogador *p, int mapa[ALTURA][LARGURA]) {
    double agora = GetTime(); // tempo atual em segundos
    
    if (agora - p->ultimoMovimento >= p->cooldown) {
        if (IsKeyDown(KEY_D)) {
            p->x += p->velocidade;
            p->ultimoMovimento = agora;
        } else if (IsKeyDown(KEY_A)) {
            p->x -= p->velocidade;
            p->ultimoMovimento = agora;
        } else if (IsKeyDown(KEY_W)) {
            p->y -= p->velocidade;
            p->ultimoMovimento = agora;
        } else if (IsKeyDown(KEY_S)) {
            p->y += p->velocidade;
            p->ultimoMovimento = agora;
        }
    }
}

void AtualizarPersonagem2(Jogador *p, int mapa[ALTURA][LARGURA]) {
    double agora = GetTime(); // tempo atual em segundos
    
    if (agora - p->ultimoMovimento >= p->cooldown) {
        if (IsKeyDown(KEY_RIGHT)) {
            p->x += p->velocidade;
            p->ultimoMovimento = agora;
        } else if (IsKeyDown(KEY_LEFT)) {
            p->x -= p->velocidade;
            p->ultimoMovimento = agora;
        } else if (IsKeyDown(KEY_UP)) {
            p->y -= p->velocidade;
            p->ultimoMovimento = agora;
        } else if (IsKeyDown(KEY_DOWN)) {
            p->y += p->velocidade;
            p->ultimoMovimento = agora;
        }
    }
}

void DesenharPersonagem(Jogador p) {
    DrawRectangle(p.x, p.y, p.tamanho, p.tamanho, p.cor);
}


