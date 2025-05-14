// menu.c
#include "raylib.h"
#include "menu.h"

static const char *menuItems[MENU_COUNT] = {
    "START GAME",
    "OPTIONS",
    "EXIT"
};

MenuOption ShowMenu(void)
{
    int selected = 0;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Navegação
        if (IsKeyPressed(KEY_DOWN)) selected = (selected + 1) % MENU_COUNT;
        if (IsKeyPressed(KEY_UP))   selected = (selected - 1 + MENU_COUNT) % MENU_COUNT;

        if (IsKeyPressed(KEY_ENTER))
            return (MenuOption)selected;

        // Render
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Título
        DrawText("MAIN MENU", MeasureText("MAIN MENU", 40)/-2 + GetScreenWidth()/2,
                 GetScreenHeight()/4, 40, DARKBLUE);

        // Itens
        int spacing = 50;
        int startY  = GetScreenHeight()/2 - (spacing * MENU_COUNT)/2;
        for (int i = 0; i < MENU_COUNT; i++)
        {
            Color col = (i == selected) ? RED : BLACK;
            DrawText(menuItems[i],
                     MeasureText(menuItems[i], 30)/-2 + GetScreenWidth()/2,
                     startY + i*spacing,
                     30, col);
        }

        DrawText("Use UP/DOWN and ENTER to select",
                 MeasureText("Use UP/DOWN and ENTER to select", 20)/-2 + GetScreenWidth()/2,
                 GetScreenHeight() - 100, 20, DARKGRAY);

        EndDrawing();
    }

    return MENU_EXIT; // se fechar a janela
}
