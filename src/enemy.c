#include "enemy.h"


void CriarInimigo(Inimigo *p) {
    p->vida = true;
    p->velocidade = 64;
    p->x = 832;
    p->y = 832;
    p->tamanho = 64;
    p->ultimoMovimento = 0.0;
    p->direcao = NORTE;
    //
    p->frameAtual = 0;
    p->tempoFrame = 0.15;
    p->tempoUltimoFrame = GetTime();
}


void AtualizarInimigo(Inimigo *p, int mapa[ALTURA][LARGURA],Jogador *j) {
    bool seMovendo = false;
    double agora = GetTime();
    float delta = GetFrameTime();
    p->tempoUltimoFrame += delta;

    if (agora - p->ultimoMovimento >= 1.0) {
        int tentativas = 0;
        bool encontrou = false;
        int direcaoCandidata;
        int dx, dy, novoX, novoY;

        while (tentativas < 4 && !encontrou) {
            direcaoCandidata = rand() % 4;

            // 2) calcula o deslocamento
            dx = (direcaoCandidata == LESTE)  ? p->velocidade//se direcao leste
            : (direcaoCandidata == OESTE)  ? -p->velocidade//se direcao oeste
            : 0;//se nenhuma das direcoes
            dy = (direcaoCandidata == SUL)    ? p->velocidade//se direcao sul
            : (direcaoCandidata == NORTE)  ? -p->velocidade//se direcao norte
            : 0;//se nenhuma das direcoes
            novoX = p->x + dx;
            novoY = p->y + dy;

            // 3) converte para índice de célula
            int col = novoX / p->tamanho;
            int lin = novoY / p->tamanho;

            // 4) verifica colisão
            if (lin >= 0 && lin < ALTURA && col >= 0 && col < LARGURA
                && mapa[lin][col] == 0) {
                encontrou = true;  // caminho livre
            } else {
                tentativas++;
            }
        }

        // se encontrou direção livre, aplica movimento
        if (encontrou) {
            p->x = novoX;
            p->y = novoY;
            p->direcao = direcaoCandidata;
            p->ultimoMovimento = agora;
        }
    }
    if ((p->tempoUltimoFrame >= p->tempoFrame)&&seMovendo) {
        p->frameAtual++;
        if (p->frameAtual > 2) p->frameAtual = 0; // 3 frames: 0, 1, 2
        p->tempoUltimoFrame = 0.0f;
    }

}


void DesenharInimigo(Inimigo p) {
    Texture2D sheet = LoadTexture("resources/bomb_party_v4.png");
    const int TILE_ORIG = 16;
    Rectangle srcRect = { 0, 0, TILE_ORIG, TILE_ORIG };
    Rectangle destRect = { p.x, p.y, CELULA, CELULA };
    double agora = GetTime();

    switch (p.direcao) {
    case NORTE:
        srcRect.y = 14 * TILE_ORIG;
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
        srcRect.y = 14 * TILE_ORIG;
        srcRect.x = (p.frameAtual * TILE_ORIG)+16;
        srcRect.width = TILE_ORIG;
        break;
    case LESTE:
        srcRect.y = 14 * TILE_ORIG;
        srcRect.x = (p.frameAtual * TILE_ORIG)+64;
        srcRect.width = TILE_ORIG;
        break;
    case OESTE:
        srcRect.y = 14 * TILE_ORIG;
        srcRect.x = (p.frameAtual * TILE_ORIG)+64;
        srcRect.width = -TILE_ORIG;
        break;
    }
    DrawTexturePro(sheet, srcRect, destRect, (Vector2){0, 0}, 0.0f, WHITE);
}