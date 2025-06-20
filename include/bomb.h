// bomb.h
#ifndef BOMB_H
#define BOMB_H
#define TEMPO_EXPLODIR 2
#include <stdlib.h>

#include "player.h"
#include "game.h"


static void DesenhaExplosao(int linha, int coluna);
void AtualizaBombas(Jogador *p, int mapa[ALTURA][LARGURA]);
void SoltaBomba(Jogador *p, int mapa[ALTURA][LARGURA]);
void DesenhaBombas(const Jogador *p);
int Explodir(Bomba *b, int mapa[ALTURA][LARGURA], int tamanho);
static void DestruirBloco(int linha, int coluna, int mapa[ALTURA][LARGURA]);
static int ContarBlocos(int mapa[ALTURA][LARGURA]);

#endif // BOMB_H