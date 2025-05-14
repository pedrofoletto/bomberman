// bomb.h
#ifndef BOMB_H
#define BOMB_H

#include "player.h"

typedef struct {
    int x, y;
    int time;
    int tick;
} bomba;

void SoltaBomba(Jogador *p);

#endif // BOMB_H