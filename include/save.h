#ifndef SAVE_H
#define SAVE_H

#include "player.h" //pela struct
#include <stdbool.h>

// Struct que guarda os dados que queremos salvar
typedef struct SaveData {
    int fase;
    int score;
    int bombas;
    int range; // a gente salva esses dois? tem que
} SaveData; //fazer temporário entao

void SalvarProgresso(const Jogador *jogador, int fase);
bool CarregarProgresso(Jogador *jogador, int *fase);
bool NovoJogo(Jogador *jogador, int *fase);

#endif // SAVE_H