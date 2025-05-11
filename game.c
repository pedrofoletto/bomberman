#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define CELULA 64
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

//lê a matriz e substitui os números por retângulos
void Construir(){ 
    for (int y = 0; y < ALTURA; y++){
        for (int x = 0; x < LARGURA; x++){
            if (map[y][x] == 1){
                DrawRectangle(x * CELULA, y * CELULA, CELULA, CELULA, DARKGRAY);
            } else if (map [y][x] == 0) {
                DrawRectangle(x * CELULA, y * CELULA, CELULA, CELULA, RAYWHITE);
            } else {
                DrawRectangle(x * CELULA, y * CELULA, CELULA, CELULA, BROWN);
            }
            DrawRectangleLines(x * CELULA, y * CELULA, CELULA, CELULA, BLACK);
        }
    }
}
//função pause
void pausar(bool paused){   
    if(paused){
        DrawText("PAUSADO", 100, 200, 20, RED);
    }
    else{
        DrawText("RODANDO", 100, 200, 20, DARKBLUE); //somente para teste, dps remover
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
void Tijolos(int fase) { //fase é o máximo de tijolos que podem surgir na fase (colocar pra aumentar com as fases) 
    int colocados = 0;  
    int tentativas = 50;
    int limite = fase;

    while (colocados < limite && tentativas > 0){
        int y = rand() % ALTURA;
        int x = rand() % LARGURA;

        if (map[y][x] == 0 && !(map[1][1])){
            map[y][x] = 2; //coloca tijolo
            colocados++;
        }
        tentativas--;
    }
}

int main (){
    int fase = 2; //número de tijolos

    InitWindow(LARGURA * CELULA, ALTURA * CELULA, "Mini Bomberman");
    SetExitKey(0);
    SetTargetFPS(60); //verificar ainda quantos fps devem ter
    
    bool paused = false;

    srand(time(NULL));

    Tijolos(fase); //2 tijolo

    //game loop
    while(!WindowShouldClose())
    {
    if (IsKeyPressed(KEY_ESCAPE))
        paused = !paused;

    
     //event handling

     //updating positions 

     //drawing
    BeginDrawing();
    ClearBackground(WHITE);
    Construir();
    pausar(paused);
    EndDrawing();
    }

    CloseWindow();
    return 0;
}

