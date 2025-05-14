#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SCREEN_W 64*15
#define SCREEN_H 1080
#define CELULA 64
#define LARGURA 15
#define ALTURA 15
#define MAXINIMIGOS 5


//lê a matriz e substitui os números por retângulos
void Construir(int *mapa) { 
    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            int valor = *(mapa + y * LARGURA + x);

            if (valor == 1) {
                DrawRectangle(x * CELULA, y * CELULA, CELULA, CELULA, DARKGRAY);
            } else if (valor == 0) {
                DrawRectangle(x * CELULA, y * CELULA, CELULA, CELULA, RAYWHITE);
            } else{
                DrawRectangle(x * CELULA, y * CELULA, CELULA, CELULA, BROWN);
            }

            DrawRectangleLines(x * CELULA, y * CELULA, CELULA, CELULA, BLACK);
        }
    }
}

//função pause
void pausar(bool paused){   
    if(paused){
        DrawText("PAUSADO", (LARGURA * CELULA)/2 - 165, (LARGURA * CELULA)/2, 80, RED);
    }
    else{
        //DrawText("RODANDO", (LARGURA * CELULA)/2 - 62, (LARGURA * CELULA)/2 - 32, 20, RED); //somente para teste, dps remover
    }
}
//converte o arquivo txt do professor para a minha matriz int
int Conversao(char c) {
    switch (c) {
        case 'w': return 1; // parede
        case 'b': return 2; // tijolo
        case ' ': return 0; // vazio
        default: return 0;  // trata qualquer outro como vazio
    }
}

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


