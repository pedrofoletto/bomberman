#include "bomb.h"
#include <time.h>

void SoltaBomba(Jogador *p, int mapa[ALTURA][LARGURA]) {
    if (p->bombas == 0) return;
    for (int i = 0; i < MAX_BOMBAS; i++) {
        if (!p->listaBombas[i].ativa) {
            // inicializa bomba
            p->listaBombas[i].ativa = true;
            p->listaBombas[i].time  = GetTime();
            p->listaBombas[i].tick  = 0;
            p->listaBombas[i].range = 2;
            p->listaBombas[i].tempo_explosao = 2;
            // posicione na célula do jogador
            p->listaBombas[i].x = (p->x / p->tamanho);
            p->listaBombas[i].y = (p->y / p->tamanho);
            // marca no mapa
            mapa[p->listaBombas[i].y][p->listaBombas[i].x] = 3;
            break;
        }
    }
}
void AtualizaBombas(Jogador *p, int mapa[ALTURA][LARGURA],infJogo *jogo) {
    for (int i = 0; i < MAX_BOMBAS; i++) {
        Bomba *b = &p->listaBombas[i];
        if (!b->ativa) continue;

        if ((GetTime()-b->time)>=TEMPO_EXPLODIR) {
            Explodir(b, mapa, p->tamanho);
            p->bombas++;
            b->ativa = false;
            mapa[b->y][b->x] = 0;
        }
    }
}

static void DesenhaExplosao(int linha, int coluna) {
    DrawRectangle((coluna * CELULA),(linha  * CELULA), CELULA, CELULA, ORANGE);
}


void DesenhaBombas(const Jogador *p) {
    for (int i = 0; i < MAX_BOMBAS; i++) {
        const Bomba *b = &p->listaBombas[i];
        if (!b->ativa) continue;
        DrawRectangle(b->x * p->tamanho, b->y * p->tamanho,p->tamanho, p->tamanho, YELLOW);
    }
}

void Explodir(Bomba *b, int mapa[ALTURA][LARGURA], int tamanho) {

    DesenhaExplosao(b->y, b->x);

    for (int dir = 0; dir < 4; dir++) {//direções
        int direcaox = 0, direcaoy = 0;
        switch (dir) {
            case 0: direcaox =  1; break;
            case 1: direcaox = -1; break; 
            case 2: direcaoy =  1; break; 
            case 3: direcaoy = -1; break; 
        }
        for (int step = 1; step <= b->range; step++) {//verifica se tem tijolo ou parede
            int verificandox = b->x + direcaox * step;
            int verificandoy = b->y + direcaoy * step;

            if (verificandox < 0 || verificandox >= LARGURA || verificandoy < 0 || verificandoy >= ALTURA) break;

            if (mapa[verificandoy][verificandox] == 1) { //se for parede
                break;
            }

            if (mapa[verificandoy][verificandox] == 2){//se for tijolo
                DestruirBloco(verificandoy, verificandox, mapa);
                break;
            } 
            //se for vazio
            DesenhaExplosao(verificandoy, verificandox);
        }
    }
    b->ativa = false;//desativa a bomba
}

static void DestruirBloco(int linha, int coluna, int mapa[ALTURA][LARGURA]) {
    if (mapa[linha][coluna] == 2) {
        mapa[linha][coluna] = 0;
        //ve quantos tijolos tem e calcula a probalidade de abrir um power up ou um portal
        int probabilidadePower = rand() % 100;
        int probabilidadePortal = rand() % fase;
        if (probabilidadePower < 20) {
            // Power-up
            mapa[linha][coluna] = 4; // Representa um power-up
        } else if (probabilidade < 30) {
            // Portal
            mapa[linha][coluna] = 5; // Representa um portal
        }
        
    }
}