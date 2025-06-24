// Em include/bomb.h

#ifndef BOMB_H
#define BOMB_H

#include "player.h"
#include "game.h"

#define TEMPO_EXPLODIR 2.0   
#define TEMPO_DURACAO_EXPLOSAO 0.5 

void AtualizaBombas(Jogador *p, int mapa[ALTURA][LARGURA]);

void SoltaBomba(Jogador *p, int mapa[ALTURA][LARGURA]);
void DesenhaBombas(const Jogador *p, Texture2D sheet, int mapa[ALTURA][LARGURA]);


static void DestruirBloco(int linha, int coluna, int mapa[ALTURA][LARGURA]);
static int ContarBlocos(int mapa[ALTURA][LARGURA]);

#endif // BOMB_H