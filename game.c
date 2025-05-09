#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define CELULA 32
#define LARGURA 15
#define ALTURA 15
#define MAXINIMIGOS 5
int map[ALTURA][LARGURA] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int Conversao(char c) {
    switch (c) {
        case 'w': return 1; // parede
        case 'b': return 2; // tijolo
        case ' ': return 0; // vazio
        default: return 0;  // trata qualquer outro como vazio
    }
}


void Tijolos(int fase) { //fase é o máximo de tijolos que podem surgir na fase (colocar pra aumentar com as fases)
    srand(time(NULL));  
    int colocados = 0;  
    int tentativas = 50;
    int limite = fase;

    while (colocados < limite && tentativas > 0){
        int y = rand() % ALTURA;
        int x = rand() % LARGURA;

        if (map[y][x] == 0){
            map [y][x] = 2; //coloca tijolo
            colocados++;
        }
        tentativas--;
    }
}

int main (){
    int fase = 2; //número de tijolos
    InitWindow(LARGURA * CELULA, ALTURA * CELULA, "Mini Bomberman");
    SetTargetFPS(60);

    Tijolos(fase); //2 tijolo


typedef struct //ficha geral do Inimigo
{
    int vida; //quantas bombas ele leva pra morrer
    int comportamento; //ver se faremos diferente
    int nome;
    int estado; //vivo ou morto
} inimigo;

    inimigo inimigos[MAXINIMIGOS];
    for (int i = 0; i > MAXINIMIGOS; i++){ //deixar analisando durante jogo, botar no loop
        if (inimigos[i].vida = 0){ //setar para inimigo, aprender a usar struct
            //no lugar que morreu, chance de saída
            int mortos = 0;
            int chancesaida = 10;
            srand(time(NULL));
            for(int i = 0; i < 10; i++){ //10 máx inimigos
                int chanceatual = chancesaida + 10 * mortos; //aumenta chance da segunda saída
                int talvezsaida = rand() % 100;
    
                if (talvezsaida < chanceatual){
                //criar saída
                }  
            }
        }
    }
}