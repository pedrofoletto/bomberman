#include "bomb.h"
#include <time.h>
#include <stdlib.h>

void SoltaBomba(Jogador *p, int mapa[ALTURA][LARGURA]) {
    if (p->bombas == 0) return;
    for (int i = 0; i < MAX_BOMBAS; i++) {
        if (p->listaBombas[i].state == BOMB_STATE_INACTIVE) {
            Bomba *b = &p->listaBombas[i];
            
            b->state = BOMB_STATE_TICKING;
            b->time  = GetTime();
            b->range = 2;
            b->x = (p->x / p->tamanho);
            b->y = (p->y / p->tamanho);
            
            b->frameAtual = 0;
            b->tempoFrame = 0.25;
            b->tempoUltimoFrame = 0.0;
            b->tempoVisivelExplosao = 0.0;
            
            p->bombas--; 
            break;
        }
    }
}


void AtualizaBombas(Jogador *p, int mapa[ALTURA][LARGURA]) {
    for (int i = 0; i < MAX_BOMBAS; i++) {
        Bomba *b = &p->listaBombas[i];

        if (b->state == BOMB_STATE_TICKING) {
            b->tempoUltimoFrame += GetFrameTime();
            if (b->tempoUltimoFrame >= b->tempoFrame) {
                b->tempoUltimoFrame = 0.0;
                b->frameAtual = (b->frameAtual + 1) % 3;
            }

            if (GetTime() - b->time >= TEMPO_EXPLODIR) {
                b->state = BOMB_STATE_EXPLODING;
                b->time = GetTime();
                
                int explosoes = 0;

                // d,e,b,c
                int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
                int *reaches[] = {&b->reachRight, &b->reachLeft, &b->reachDown, &b->reachUp};

                for(int d = 0; d < 4; d++) {
                    *(reaches[d]) = 0; // inicia o range
                    for (int r = 1; r <= b->range; r++) {
                        int nextX = b->x + dirs[d][0] * r;
                        int nextY = b->y + dirs[d][1] * r;

                        if (nextX < 0 || nextX >= LARGURA || nextY < 0 || nextY >= ALTURA) break;
                        if (mapa[nextY][nextX] == 1) break;

                        *(reaches[d]) = r; // aumenta alcance, não mexa

                        if (mapa[nextY][nextX] == 2) {
                            explosoes++;
                            DestruirBloco(nextY, nextX, mapa);
                            break; // para no tijolo
                        }
                    }
                }
                p->score += explosoes;
            }
        } else if (b->state == BOMB_STATE_EXPLODING) {
            if (GetTime() - b->time >= TEMPO_DURACAO_EXPLOSAO) {
                b->state = BOMB_STATE_INACTIVE;
                if (p->bombas < 1) p->bombas++;
            }
        }
    }
}

void DesenhaBombas(const Jogador *p, Texture2D sheet, int mapa[ALTURA][LARGURA]) {
    const int TILE_ORIG = 16;
    Rectangle srcRect = { 0, 0, TILE_ORIG, TILE_ORIG };
    Rectangle dstRect = { 0, 0, CELULA, CELULA };
    Vector2 origin = { 0, 0 };

    const Rectangle spritesExplosao[] = {
        [0] = {2 * TILE_ORIG, 18 * TILE_ORIG, TILE_ORIG, TILE_ORIG}, // Centro
        [1] = {1 * TILE_ORIG, 18 * TILE_ORIG, TILE_ORIG, TILE_ORIG}, // Meio Horizontal
        [2] = {14 * TILE_ORIG, 14 * TILE_ORIG, TILE_ORIG, TILE_ORIG}, // Meio Vertical
        [3] = {3 * TILE_ORIG, 18 * TILE_ORIG, TILE_ORIG, TILE_ORIG}, // Ponta Direita
        [4] = {0 * TILE_ORIG, 18 * TILE_ORIG, TILE_ORIG, TILE_ORIG}, // Ponta Esquerda
        [5] = {14 * TILE_ORIG, 15 * TILE_ORIG, TILE_ORIG, TILE_ORIG}, // Ponta Baixo
        [6] = {14 * TILE_ORIG, 13 * TILE_ORIG, TILE_ORIG, TILE_ORIG}  // Ponta Cima
    };

    for (int i = 0; i < MAX_BOMBAS; i++) {
        const Bomba *b = &p->listaBombas[i];

        if (b->state == BOMB_STATE_INACTIVE) continue;

        if (b->state == BOMB_STATE_TICKING) {
            srcRect.y = 18 * TILE_ORIG;
            srcRect.x = (b->frameAtual + 5) * TILE_ORIG; //a bomba tá indo e reiniciando e nao to com saco pra arrumar, teria que mudar tempo e tick
            dstRect.x = b->x * CELULA;
            dstRect.y = b->y * CELULA;
            DrawTexturePro(sheet, srcRect, dstRect, origin, 0.0f, WHITE);

        } else if (b->state == BOMB_STATE_EXPLODING) {
            // 1. Desenha o centro da explosão
            dstRect.x = b->x * CELULA;
            dstRect.y = b->y * CELULA;
            DrawTexturePro(sheet, spritesExplosao[0], dstRect, origin, 0.0f, WHITE);

            const int reaches[] = {b->reachRight, b->reachLeft, b->reachDown, b->reachUp};
            const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            const int spriteMeio[] = {1, 1, 2, 2}; // meio h h v v 
            const int spritePonta[] = {3, 4, 5, 6};  //D, E, B, C

            for (int d = 0; d < 4; d++) {
                for (int r = 1; r <= reaches[d]; r++) {
                    int spriteIdx = (r == reaches[d]) ? spritePonta[d] : spriteMeio[d];
                    
                    dstRect.x = (b->x + dirs[d][0] * r) * CELULA;
                    dstRect.y = (b->y + dirs[d][1] * r) * CELULA;
                    DrawTexturePro(sheet, spritesExplosao[spriteIdx], dstRect, origin, 0.0f, WHITE);
                }
            }
        }
    }
}

static void DestruirBloco(int linha, int coluna, int mapa[ALTURA][LARGURA]) {
    if (mapa[linha][coluna] == 2) {
        if (ContarBlocos(mapa) == 1) {
            mapa[linha][coluna] = 4;
        } else {
            mapa[linha][coluna] = 0;
            if ((rand() % 100) < 20) {
                mapa[linha][coluna] = 3;
            }
        }
    }
}

static int ContarBlocos(int mapa[ALTURA][LARGURA]) {
    int count = 0;
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (mapa[i][j] == 2) {
                count++;
            }
        }
    }
    return count;
}