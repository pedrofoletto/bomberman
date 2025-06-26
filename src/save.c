#include "save.h"
#include <stdio.h> 

#define SAVE_FILE "savegame.bin"

void SalvarProgresso(const Jogador *jogador, int fase) {
    // 1. Prepara a struct com os dados atuais
    SaveData dados;
    dados.fase = fase;
    dados.score = jogador->score;
    dados.bombas = jogador->bombas;
    
    // --- CORREÇÃO AQUI ---
    // Verifica se a primeira bomba NÃO está inativa para ler o seu range.
    if (jogador->listaBombas[0].state != BOMB_STATE_INACTIVE) {
         dados.range = jogador->listaBombas[0].range;
    } else {
         // Se a primeira bomba estiver inativa, podemos assumir um valor padrão
         // ou procurar por outra bomba ativa, mas para um jogo de uma bomba, isto é suficiente.
         dados.range = 2; // Valor padrão inicial do range
    }

    // 2. Abre o ficheiro em modo de escrita binária ("wb")
    FILE *arquivo = fopen(SAVE_FILE, "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o ficheiro para salvar");
        return;
    }

    fwrite(&dados, sizeof(SaveData), 1, arquivo);

    fclose(arquivo);

    printf("salvo na fase %d\n", fase);
}

bool CarregarProgresso(Jogador *jogador, int *fase) {
    // 1. Abre o ficheiro em modo de leitura binária ("rb")
    FILE *arquivo = fopen(SAVE_FILE, "rb");
    if (arquivo == NULL) {
        // Se o ficheiro não existir, não é um erro. Apenas não há nada para carregar.
        printf("Nenhum progresso salvo encontrado. Comecando novo jogo.\n");
        return false;
    }

    // 2. Lê os dados do ficheiro para a nossa struct
    SaveData dados;
    fread(&dados, sizeof(SaveData), 1, arquivo);

    // 3. Fecha o ficheiro
    fclose(arquivo);

    // 4. Atualiza as variáveis do jogo com os dados carregados
    *fase = dados.fase;
    jogador->score = dados.score;
    jogador->bombas = dados.bombas;
    
    // Atualiza o range das bombas
    for (int i = 0; i < MAX_BOMBAS; i++) {
        jogador->listaBombas[i].range = dados.range;
    }

    printf("Progresso carregado! Continuando da fase %d.\n", *fase);
    return true;
}