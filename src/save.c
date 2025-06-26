#include "save.h"
#include <stdio.h> 

#define SAVE_FILE "savegame.bin"

void SalvarProgresso(const Jogador *jogador, int fase) {
    SaveData dados;
    dados.fase = fase;
    dados.score = jogador->score;
    dados.bombas = jogador->bombas;
    
    if (jogador->listaBombas[0].state != BOMB_STATE_INACTIVE) {
         dados.range = jogador->listaBombas[0].range;
    } else {
         dados.range = 2; // valor padrao que escolhi
    }

    FILE *arquivo = fopen(SAVE_FILE, "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para slavar");
        return;
    }

    fwrite(&dados, sizeof(SaveData), 1, arquivo);

    fclose(arquivo);

    //printf("salvo na fase %d\n", fase);
}

bool CarregarProgresso(Jogador *jogador, int *fase) {
    FILE *arquivo = fopen(SAVE_FILE, "rb");
    if (arquivo == NULL) {
        printf("sem progresso, criando novo jogo...\n");
        return false;
    }

    SaveData dados;
    fread(&dados, sizeof(SaveData), 1, arquivo);

    fclose(arquivo);

    *fase = dados.fase;
    jogador->score = dados.score;
    jogador->bombas = dados.bombas;
    
    for (int i = 0; i < MAX_BOMBAS; i++) {
        jogador->listaBombas[i].range = dados.range;
    }

    printf("continuando jogo: fase %d.\n", *fase);
    return true;
}