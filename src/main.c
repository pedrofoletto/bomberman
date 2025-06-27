#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "game.h"
#include "menu.h"
#include "bomb.h"
#include "enemy.h"
#include "level.h"
#include <stdio.h> 
#include "save.h"

#define SCREEN_W 64*15
#define SCREEN_H 1080
#define CELULA 64
#define LARGURA 15
#define ALTURA 15
#define MAXINIMIGOS 5

typedef enum GameScreen { MENU = 0, OPCOES, GAMEPLAY,LEVEL_COMPLETE ,ENDING, RESUME, GAME_OVER } GameScreen;

void ReiniciarJogo(int *fase, Jogador *jogador, Inimigo *inimigo1, Inimigo *inimigo2, int mapa[ALTURA][LARGURA]) {
    *fase = 1; 
    SetupLevel(jogador, inimigo1, inimigo2, mapa, *fase);
    jogador->vida = true; 
    jogador->score = 0;
    inimigo1->vida = true;
    inimigo2->vida = true;
}

void ResetarMapaParaPadrao(int mapa[ALTURA][LARGURA]) {
    int mapaPadrao[ALTURA][LARGURA] = {
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

    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            mapa[i][j] = mapaPadrao[i][j];
        }
    }
}

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


    infJogo jogo;

    jogo.multiplayer = false;
    int fase = 1;
    jogo.fase = fase;
    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            jogo.mapa[i][j] = mapa[i][j];
        }
    }

    Jogador pedro;
    Inimigo inimigo1;
    Inimigo inimigo2;
    CriarPersonagem(&pedro);

    if (!CarregarProgresso(&pedro, &fase)) {
        fase = 1;
        pedro.score = 0;
    }
    
    CriarInimigo(&inimigo1);
    CriarInimigo(&inimigo2);

    for (int i = 0; i < MAX_BOMBAS; i++) {
        pedro.listaBombas[i].state = BOMB_STATE_INACTIVE;
    }

    GameScreen currentScreen = MENU;
    
    InitWindow(SCREEN_W, SCREEN_H, "Mini Bomberman");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    srand(time(NULL));
    InitAudioDevice();
    Music musica = LoadMusicStream("resources/jogo.ogg");
    Tijolos(&mapa[0][0], fase);

    
    Texture2D sheet = LoadTexture("resources/bomb_party_v4.png");
    while(!WindowShouldClose())
    {
        // logica
        UpdateMusicStream(musica);
        switch (currentScreen)
        {
            case MENU:
            {
                MenuOption choice = ShowMenu();
                if (choice == MENU_START){
                    NovoJogo(&pedro, &fase);
                    currentScreen = GAMEPLAY;
                    PlayMusicStream(musica);
                }   
                else if (choice == MENU_CONTINUE)//carrega save
                {
                    if (CarregarProgresso(&pedro, &fase)) {
                        SetupLevel(&pedro, &inimigo1, &inimigo2, mapa, fase);
                        currentScreen = GAMEPLAY;
                        PlayMusicStream(musica);
                    }
                }
                else if (choice == MENU_OPTIONS) {currentScreen = OPCOES;}
                else if (choice == MENU_EXIT)  
                CloseWindow();
                continue;

            } break;
            case OPCOES:{
                if (IsKeyPressed(KEY_L))
                {
                    if (CarregarMapa("../maps/custom_map.bin", mapa)){
                        CriarPersonagem(&pedro);
                        CriarInimigo(&inimigo1);
                        CriarInimigo(&inimigo2);
                        currentScreen = MENU;
                    }
                }
                if (IsKeyPressed(KEY_ESCAPE)){
                    currentScreen = MENU;
                }
            } break;

            case GAMEPLAY:
            {   
                if (IsKeyPressed(KEY_ESCAPE)){ 
                PauseMusicStream(musica);
                currentScreen = RESUME;
                }

                int playerStatus = AtualizarPersonagem(&pedro, mapa);
                AtualizaBombas(&pedro, mapa);
                if (inimigo1.vida) AtualizarInimigo(&inimigo1, mapa, &pedro);
                if (inimigo2.vida) AtualizarInimigo(&inimigo2, mapa, &pedro);

                Rectangle playerRec = { pedro.x, pedro.y, pedro.tamanho, pedro.tamanho };
                Rectangle enemy1Rec = { inimigo1.x, inimigo1.y, inimigo1.tamanho, inimigo1.tamanho };
                Rectangle enemy2Rec = { inimigo2.x, inimigo2.y, inimigo2.tamanho, inimigo2.tamanho };

                if (inimigo1.vida && CheckCollisionRecs(playerRec, enemy1Rec)) {
                    pedro.vida = false;
                }
                if (inimigo2.vida && CheckCollisionRecs(playerRec, enemy2Rec)) {
                    pedro.vida = false;
                }
                //pra bomba
                for (int i = 0; i < MAX_BOMBAS; i++) {
                    if (pedro.listaBombas[i].state == BOMB_STATE_EXPLODING) {
                        Bomba *b = &pedro.listaBombas[i];
                        
                        Rectangle explosaoCentro = { b->x * CELULA, b->y * CELULA, CELULA, CELULA };
                        if (CheckCollisionRecs(playerRec, explosaoCentro)) pedro.vida = false;
                        if (inimigo1.vida && CheckCollisionRecs(enemy1Rec, explosaoCentro)) { inimigo1.vida = false; pedro.score += 100; }
                        if (inimigo2.vida && CheckCollisionRecs(enemy2Rec, explosaoCentro)) { inimigo2.vida = false; pedro.score += 100; }
                        
                        const int reaches[] = {b->reachRight, b->reachLeft, b->reachDown, b->reachUp};
                        const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

                        for (int d = 0; d < 4; d++) {
                            for (int r = 1; r <= reaches[d]; r++) {
                                Rectangle explosaoParte = { (b->x + dirs[d][0] * r) * CELULA, (b->y + dirs[d][1] * r) * CELULA, CELULA, CELULA };
                                
                                if (CheckCollisionRecs(playerRec, explosaoParte)) pedro.vida = false;
                                if (inimigo1.vida && CheckCollisionRecs(enemy1Rec, explosaoParte)) { inimigo1.vida = false; pedro.score += 100; }
                                if (inimigo2.vida && CheckCollisionRecs(enemy2Rec, explosaoParte)) { inimigo2.vida = false; pedro.score += 100; }
                            }
                        }
                    }
                }

                if (!pedro.vida) {
                    currentScreen = GAME_OVER;
                }

                if (playerStatus == 1) {
                    printf("%d", playerStatus);
                    currentScreen = LEVEL_COMPLETE;
                }
                
            } break;
            case LEVEL_COMPLETE:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    fase++;
                    SalvarProgresso(&pedro, fase);
                    SetupLevel(&pedro, &inimigo1, &inimigo2, mapa, fase);
                    currentScreen = GAMEPLAY;
                }
            } break;
            
            case GAME_OVER:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    ReiniciarJogo(&fase, &pedro, &inimigo1, &inimigo2, mapa);
                    SalvarProgresso(&pedro, fase);
                    currentScreen = GAMEPLAY;
                }
                if (IsKeyPressed(KEY_Q))
                {
                    StopMusicStream(musica);
                    ResetarMapaParaPadrao(mapa); // Restaura o mapa
                    currentScreen = MENU;
                }
            } break;
            case ENDING:
            {
                if (IsKeyPressed(KEY_ENTER)) currentScreen = MENU;
            } break;
            case RESUME:
            {
                if (IsKeyPressed(KEY_ESCAPE)){ 
                    ResumeMusicStream(musica);
                    currentScreen = GAMEPLAY;
                }
                if (IsKeyPressed(KEY_Q))
    {
        StopMusicStream(musica);

        currentScreen = MENU;
    }
            } break;
            default: break;
        }

        // Desenho
        #define CENTER_X(txt, size) (SCREEN_W/2 - MeasureText(txt, size)/2)

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        switch (currentScreen)
        {
            case MENU:
            {
                // showmenu tá desenhando, não sei se dá pra apagar
            } break;
            case OPCOES:{
                DrawRectangle(0, 0, SCREEN_W, SCREEN_H, DARKGRAY);
                const char *t1 = "Opcoes";
                const char *t2 = "Pressione [L] para Carregar Mapa Personalizado";
                const char *t3 = "Pressione [ESC] para Voltar";

                DrawText(t1, CENTER_X(t1, 40), SCREEN_H/2 - 80, 40, WHITE);
                DrawText(t2, CENTER_X(t2, 20), SCREEN_H/2, 20, LIGHTGRAY);
                DrawText(t3, CENTER_X(t3, 20), SCREEN_H/2 + 40, 20, LIGHTGRAY);
            } break;
            case GAMEPLAY:
            {

                Construir(&mapa[0][0], sheet);
                if (inimigo1.vida) DesenharInimigo(inimigo1, sheet);
                if (inimigo2.vida) DesenharInimigo(inimigo2, sheet);
                if (pedro.vida) DesenharPersonagem(pedro, sheet);
                DesenhaBombas(&pedro, sheet, mapa);
                
                EscreverInfo(fase, pedro.score, pedro.bombas, pedro.alcance);

            } break;
            case LEVEL_COMPLETE:
            {
                const char *l1 = "Parabéns";
                const char *l2 = "ENTER para continuar";
                const char *l3 = "ESC do EXIT";
                DrawRectangle(0, 0, SCREEN_W, SCREEN_H, PURPLE);
                DrawText(l1, CENTER_X(l1, 40), SCREEN_H/2 - 30, 40, DARKPURPLE);
                DrawText(l2, CENTER_X(l2, 20), SCREEN_H/2 + 30, 20, DARKPURPLE);
                DrawText(l3, CENTER_X(l3, 20), SCREEN_H/2 + 60, 20, DARKPURPLE);
            } break;
            case GAME_OVER:
            {
                const int TAMANHO_TITULO = 40;
                const int TAMANHO_SUBTITULO = 20;
                const int ESPACAMENTO_VERTICAL = 30;

                const char *go1 = "MORREU";
                const char *go2 = "ENTER para Reiniciar";
                const char *go3 = "(Q) para voltar ao Menu";
                const char *scoreText = TextFormat("Score: %d", pedro.score);
                

                DrawRectangle(0, 0, SCREEN_W, SCREEN_H, BLACK);
                DrawText(go1, CENTER_X(go1, TAMANHO_TITULO), SCREEN_H/2 - ESPACAMENTO_VERTICAL, TAMANHO_TITULO, RED);
                DrawText(scoreText, CENTER_X(scoreText, TAMANHO_SUBTITULO), SCREEN_H/2 + ESPACAMENTO_VERTICAL, TAMANHO_SUBTITULO, WHITE);
                DrawText(go2, CENTER_X(go2, TAMANHO_SUBTITULO), SCREEN_H/2 + (ESPACAMENTO_VERTICAL*2), TAMANHO_SUBTITULO, WHITE);
                DrawText(go3, CENTER_X(go3, TAMANHO_SUBTITULO), SCREEN_H/2 + (ESPACAMENTO_VERTICAL*3), TAMANHO_SUBTITULO, WHITE);
             } break;
            case ENDING:
            {
                const char *e1 = "ENDING SCREEN";
                const char *e2 = "ENTER para voltar";
                DrawRectangle(0, 0, SCREEN_W, SCREEN_H, BLUE);
                DrawText(e1, CENTER_X(e1, 40), SCREEN_H/2 - 30, 40, DARKBLUE);
                DrawText(e2, CENTER_X(e2, 20), SCREEN_H/2 + 30, 20, DARKBLUE);
            } break;
            case RESUME:
            {
                const char *r1 = "Precisando de um tempo?";
                const char *r2 = "ESC para voltar ao jogo";
                const char *r3 = "pressione [Q] para voltar ao menu";
                DrawRectangle(0, 0, SCREEN_W, SCREEN_H, BLACK);
                DrawText(r1, CENTER_X(r1, 40), SCREEN_H/2 - 40, 40, WHITE);
                DrawText(r2, CENTER_X(r2, 20), SCREEN_H/2 + 20, 20, WHITE);
                DrawText(r3, CENTER_X(r3, 20), SCREEN_H/2 + 50, 20, WHITE);
            } break;
            default: break;
        }
        EndDrawing();
    }
    UnloadTexture(sheet);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}