#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "game.h"
#include "menu.h"


#define CELULA 64
#define LARGURA 15
#define ALTURA 15
#define MAXINIMIGOS 5




int main (){

    int mapa[ALTURA][LARGURA] = {
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

    Jogador pedro;

    CriarPersonagem(&pedro);

    int fase = 2; //número de tijolos
    InitWindow(LARGURA * CELULA, ALTURA * CELULA, "Mini Bomberman");
    //SetExitKey(0);
    SetTargetFPS(60); //verificar ainda quantos fps devem ter
    
    bool paused = false;

    srand(time(NULL));

    Tijolos(&mapa[0][0], fase);

    //game loop
    while(!WindowShouldClose())
    {
    if (IsKeyPressed(KEY_ESCAPE))
        paused = !paused;

    
    BeginDrawing();
    //ClearBackground(WHITE);
    AtualizarPersonagem(&pedro, mapa);
    Construir(&mapa[0][0]);
    DesenharPersonagem(pedro);
    pausar(paused);

    EndDrawing();
    }

    CloseWindow();
    return 0;
}