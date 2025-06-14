#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_W 64*15
#define SCREEN_H 1080
#define CELULA 64
#define LARGURA 15
#define ALTURA 15
#define MAXINIMIGOS 5




//lê a matriz e substitui os números por retângulos
void Construir(int *mapa, Texture2D sheet) { 
    const int TILE_ORIG = 16;  // tamanho no PNG
    Rectangle srcRect = { 0, 0, TILE_ORIG, TILE_ORIG };//define o retangulo de origem
    Rectangle dstRect = { 0, 0, CELULA, CELULA };//define o retangulo de destino
    Vector2 origin = { 0, 0 };//define a origem do retangulo

    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            int valor = *(mapa + y * LARGURA + x);

            // Ajusta o srcRect.x/y conforme o tile desejado no sheet
            switch (valor) {
                case 1: // parede
                    if (((y ==ALTURA-1)||((x>0&&x<LARGURA-1)&&y==0))) {
                        srcRect.x = 0 * TILE_ORIG;
                        srcRect.y = 12 * TILE_ORIG;
                    } else if ( x > 0 && x < LARGURA-1
                        && y > 0 && y < ALTURA-1     
                        && x % 2 == 0                
                        && y % 2 == 0 )              
                        { 
                        srcRect.x = 0 * TILE_ORIG;
                        srcRect.y = 12 * TILE_ORIG;
                    }else{
                        srcRect.x = 0 * TILE_ORIG;
                        srcRect.y = 0 * TILE_ORIG;
                    }
                    break;
                case 0: // chão
                    srcRect.x = 1 * TILE_ORIG;
                    srcRect.y = 2 * TILE_ORIG;
                    break;
                case 2: // tijolo
                    srcRect.x = 9 * TILE_ORIG;
                    srcRect.y = 13 * TILE_ORIG;
                    break;
                default:
                srcRect.x = 1 * TILE_ORIG;
                srcRect.y = 2 * TILE_ORIG;
            }

            // Posição/destino na tela
            dstRect.x = x * CELULA;
            dstRect.y = y * CELULA;

            // Desenha o tile expandido de 16×16 → 64×64
            DrawTexturePro(sheet, srcRect, dstRect, origin, 0.0f, WHITE);

        }
    }
}

//função pause

//coloca tijolos aleatórios onde não é parede
void Tijolos(int *mapa, int fase) {
    int colocados = 0;  
    int tentativas = 50;
    int limite = fase;

    while (colocados < limite && tentativas > 0){
        int y = rand() % ALTURA;
        int x = rand() % LARGURA;

        // Acessa via ponteiro
        if (*(mapa + y * LARGURA + x) == 0 && !(x == 1 && y == 1)) {
            *(mapa + y * LARGURA + x) = 2;
            colocados++;
        }

        tentativas--;
    }
}

bool CarregarMapa(const char *nomeArquivo, int mapa[ALTURA][LARGURA]) {
    printf("[DEBUG] A entrar na funcao CarregarMapaDeArquivo para o ficheiro: %s\n", nomeArquivo);

    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        perror("[ERRO] Fopen falhou dentro de CarregarMapaDeArquivo");
        return false;
    }
    printf("[DEBUG] Ficheiro aberto com sucesso.\n");

    // --- PONTO CRÍTICO ---
    printf("[DEBUG] A preparar para ler o ficheiro com fread()...\n");
    size_t elementosLidos = fread(mapa, sizeof(int), ALTURA * LARGURA, arquivo);
    printf("[DEBUG] A chamada a fread() foi concluida.\n");
    // --- FIM DO PONTO CRÍTICO ---

    fclose(arquivo);
    printf("[DEBUG] Ficheiro fechado.\n");

    if (elementosLidos != ALTURA * LARGURA) {
        printf("[ERRO] O numero de elementos lidos (%zu) e diferente do esperado (%d).\n", elementosLidos, ALTURA * LARGURA);
        return false;
    }

    printf("[DEBUG] Mapa carregado com sucesso da funcao.\n");
    return true;
}

