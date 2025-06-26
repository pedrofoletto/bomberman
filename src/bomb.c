#include "bomb.h"
#include <time.h>

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
            
            p->bombas--; // Deduz uma bomba do jogador
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
                
                // --- PRÉ-CÁLCULO DA EXPLOSÃO ---
                int explosoes = 0;

                // Para cada direção [Direita, Esquerda, Baixo, Cima]
                int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
                int *reaches[] = {&b->reachRight, &b->reachLeft, &b->reachDown, &b->reachUp};

                for(int d = 0; d < 4; d++) {
                    *(reaches[d]) = 0; // Inicializa o alcance da direção atual
                    for (int r = 1; r <= b->range; r++) {
                        int nextX = b->x + dirs[d][0] * r;
                        int nextY = b->y + dirs[d][1] * r;

                        if (nextX < 0 || nextX >= LARGURA || nextY < 0 || nextY >= ALTURA) break;
                        if (mapa[nextY][nextX] == 1) break;

                        *(reaches[d]) = r; // Aumenta o alcance real

                        if (mapa[nextY][nextX] == 2) {
                            explosoes++;
                            DestruirBloco(nextY, nextX, mapa);
                            break; // Para no tijolo
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

    for (int i = 0; i < MAX_BOMBAS; i++) {
        const Bomba *b = &p->listaBombas[i];

        if (b->state == BOMB_STATE_TICKING) { //ajustado
            srcRect.y = 18 * TILE_ORIG;
            srcRect.x = b-> frameAtual+5 * TILE_ORIG;
            dstRect.x = b->x * p->tamanho;
            dstRect.y = b->y * p->tamanho;
            DrawTexturePro(sheet, srcRect, dstRect, origin, 0.0f, WHITE);

        } else if (b->state == BOMB_STATE_EXPLODING) { 
            Vector2 spriteCentro = {2, 18};
            Vector2 spriteMeioH = {1, 18};  // Horizontal (Direita/Esquerda)
            Vector2 spriteMeioV = {14, 14}; // Vertical (Cima/Baixo)
            
            // Pontas
            Vector2 spritePontaD = {3, 18};  // Direita
            Vector2 spritePontaE = {0, 18};  // Esquerda
            Vector2 spritePontaB = {14, 15}; // Baixo
            Vector2 spritePontaC = {14, 13}; // Cima

            // 1. Desenha o Centro
            srcRect.x = spriteCentro.x * TILE_ORIG;
            srcRect.y = spriteCentro.y * TILE_ORIG;
            dstRect.x = b->x * p->tamanho;
            dstRect.y = b->y * p->tamanho;
            DrawTexturePro(sheet, srcRect, dstRect, origin, 0.0f, WHITE);
            
            // 2. Prepara para desenhar os raios
            int *reaches[] = {(int*)&b->reachRight, (int*)&b->reachLeft, (int*)&b->reachDown, (int*)&b->reachUp};
            int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Direita, Esquerda, Baixo, Cima
            Vector2 pontas[] = {spritePontaD, spritePontaE, spritePontaB, spritePontaC};
            Vector2 meios[] = {spriteMeioH, spriteMeioH, spriteMeioV, spriteMeioV}; // Note que o MeioH e MeioV são usados duas vezes


            for(int d = 0; d < 4; d++) {
                for (int r = 1; r <= *(reaches[d]); r++) {
                    bool isLastStep = (r == *(reaches[d]));
                    
                    // Escolhe o sprite (Ponta ou Meio)
                    Vector2 spriteAtual = isLastStep ? pontas[d] : meios[d];
                    
                    srcRect.x = spriteAtual.x * TILE_ORIG;
                    srcRect.y = spriteAtual.y * TILE_ORIG;
                    
                    dstRect.x = (b->x + dirs[d][0] * r) * p->tamanho;
                    dstRect.y = (b->y + dirs[d][1] * r) * p->tamanho;
                    DrawTexturePro(sheet, srcRect, dstRect, origin, 0.0f, WHITE);
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