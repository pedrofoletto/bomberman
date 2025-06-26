// menu.h
#ifndef GAME_H
#define GAME_H
#define ALTURA 15
#define LARGURA 15

typedef struct infJogo
{
    bool multiplayer;
    int fase;
    int mapa[15][15];
}infJogo;
void EscreverInfo(int fase, int score);
void Construir(int *mapa, Texture2D sheet);
int Conversao(char c);
void Tijolos(int *mapa, int fase);
bool CarregarMapa(const char *uploadmapa, int mapa[ALTURA][LARGURA]);

#endif // GAME_H
