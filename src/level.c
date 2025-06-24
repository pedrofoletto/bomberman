#include "level.h"
#include "game.h" // Adicione esta linha para ter acesso à função Tijolos

void SetupLevel(Jogador *jogador, Inimigo *inimigo1, Inimigo *inimigo2, int mapa[ALTURA][LARGURA], int fase) {
    // Limpa os blocos destrutíveis antigos e gera novos
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (mapa[i][j] != 1) { 
                mapa[i][j] = 0;
            }
        }
    }
    Tijolos(&mapa[0][0], fase);

    CriarPersonagem(jogador);
    CriarInimigo(inimigo1);
    CriarInimigo(inimigo2);
}