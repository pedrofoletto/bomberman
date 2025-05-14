// menu.h
#ifndef GAME_H
#define GAME_H

typedef struct infJogo
{
    bool multiplayer;
    int fase;
    int mapa[15][15];
}infJogo;


void Construir(int *mapa);
void pausar(bool paused);
int Conversao(char c);
void Tijolos(int *mapa, int fase);

#endif // GAME_H
