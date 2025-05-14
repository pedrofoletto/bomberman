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
    if (IsKeyDown(KEY_SPACE)) {
        
    }
    if (agora - p->ultimoMovimento >= p->cooldown) {
        int novoX = p->x;
        int novoY = p->y;

        if (IsKeyDown(KEY_D)) {
            novoX += p->velocidade;
        } else if (IsKeyDown(KEY_A)) {
            novoX -= p->velocidade;
        } else if (IsKeyDown(KEY_W)) {
            novoY -= p->velocidade;
        } else if (IsKeyDown(KEY_S)) {
            novoY += p->velocidade;
        }

        // Converte coordenadas do jogador para índices do mapa
        int coluna = novoX / p->tamanho;
        int linha = novoY / p->tamanho;

        // Verifica se não está saindo do mapa
        if (linha >= 0 && linha < ALTURA && coluna >= 0 && coluna < LARGURA) {
            // Verifica se a posição é uma parede
            if (mapa[linha][coluna] == 0) {
                p->x = novoX;
                p->y = novoY;
                p->ultimoMovimento = agora;
            }
        }
    }
}


void DesenharPersonagem(Jogador p) {
    DrawRectangle(p.x, p.y, p.tamanho, p.tamanho, p.cor);
}


