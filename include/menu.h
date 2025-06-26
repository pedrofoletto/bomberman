// menu.h
#ifndef MENU_H
#define MENU_H

typedef enum {
    MENU_START = 0,
    MENU_CONTINUE,
    MENU_OPTIONS,
    MENU_EXIT,
    MENU_COUNT    // sempre último, para contar quantas opções existem
} MenuOption;

// Exibe o menu e retorna a opção selecionada pelo usuário
MenuOption ShowMenu(void);

#endif // MENU_H
