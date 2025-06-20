#include "level.h"
// Coloque esta função antes da sua função main()
void SetupLevel(Jogador *jogador, Inimigo *inimigo1, Inimigo *inimigo2, int mapa[ALTURA][LARGURA], int fase) {
    // Limpa os blocos destrutíveis antigos e gera novos
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (mapa[i][j] != 1) { // Blocos destrutíveis
                mapa[i][j] = 0; // Limpa o bloco
            }
        }
    }
    fase++;// incrementa a fase
    Tijolos(&mapa[0][0], fase);

    // Reinicia a posição do jogador e dos inimigos
    CriarPersonagem(jogador);
    CriarInimigo(inimigo1);
    CriarInimigo(inimigo2);

    // Aqui você pode adicionar mais inimigos ou alterar a dificuldade com base na 'fase'
}