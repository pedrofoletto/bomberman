#ifndef LEVEL_H
#define LEVEL_H
#define ALTURA 15
#define LARGURA 15
#include "player.h"
#include "bomb.h"
#include "enemy.h"

void SetupLevel(Jogador *jogador, Inimigo *inimigo1, Inimigo *inimigo2, int mapa[ALTURA][LARGURA], int fase);


#endif