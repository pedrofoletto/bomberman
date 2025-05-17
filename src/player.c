#include "player.h"
#include "bomb.h"

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
    p->direcao = NORTE;


    p->frameAtual = 0;
    p->tempoFrame = 0.15;
    p->tempoUltimoFrame = GetTime();

    
    for (int i = 0; i < MAX_BOMBAS; i++) {
        p->listaBombas[i].ativa = false;
    }
}


void AtualizarPersonagem(Jogador *p, int mapa[ALTURA][LARGURA]) {
    bool seMovendo = false;
    double agora = GetTime();
    float delta = GetFrameTime();
    p->tempoUltimoFrame += delta;
    
    if (IsKeyDown(KEY_SPACE)) {//bomba
        SoltaBomba(p, mapa);
    }
    if (agora - p->ultimoMovimento >= p->cooldown) {//movimentação
        int novoX = p->x;
        int novoY = p->y;

        if (IsKeyDown(KEY_D)) {
            novoX += p->velocidade;
            p->direcao = LESTE;
            seMovendo = true;
        } else if (IsKeyDown(KEY_A)) {
            novoX -= p->velocidade;
            p->direcao = OESTE;
            seMovendo = true;
        } else if (IsKeyDown(KEY_W)) {
            novoY -= p->velocidade;
            p->direcao = NORTE;
            seMovendo = true;
        } else if (IsKeyDown(KEY_S)) {
            novoY += p->velocidade;
            p->direcao = SUL;
            seMovendo = true;
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
    if ((p->tempoUltimoFrame >= p->tempoFrame)&&seMovendo) {
        p->frameAtual++;
        if (p->frameAtual > 2) p->frameAtual = 0; // 3 frames: 0, 1, 2
        p->tempoUltimoFrame = 0.0f;
    }

}


void DesenharPersonagem(Jogador p) {
    Texture2D sheet = LoadTexture("resources/bomb_party_v4.png");
    const int TILE_ORIG = 16;
    Rectangle srcRect = { 0, 0, TILE_ORIG, TILE_ORIG };
    Rectangle destRect = { p.x, p.y, CELULA, CELULA };
    double agora = GetTime();

    switch (p.direcao) {
    case NORTE:
        srcRect.y = 17 * TILE_ORIG;
        srcRect.width = TILE_ORIG;
            if (p.frameAtual == 1)
                srcRect.x = 0 * TILE_ORIG;
            else if (p.frameAtual == 2)
                srcRect.x = 8 * TILE_ORIG;
            else // frameAtual == 3
                srcRect.x = 9 * TILE_ORIG;
                srcRect.width = TILE_ORIG;
            break;
    case SUL:
        srcRect.y = 17 * TILE_ORIG;
        srcRect.x = (p.frameAtual * TILE_ORIG)+16;
        srcRect.width = TILE_ORIG;
        break;
    case LESTE:
        srcRect.y = 17 * TILE_ORIG;
        srcRect.x = (p.frameAtual * TILE_ORIG)+64;
        srcRect.width = TILE_ORIG;
        break;
    case OESTE:
        srcRect.y = 17 * TILE_ORIG;
        srcRect.x = (p.frameAtual * TILE_ORIG)+64;
        srcRect.width = -TILE_ORIG;
        break;
}

    DrawTexturePro(sheet, srcRect, destRect, (Vector2){0, 0}, 0.0f, WHITE);
}



