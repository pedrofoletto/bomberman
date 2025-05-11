#include <raylib.h>
#include <stdio.h>

void personagem(){
    typedef struct jogador{
    bool vida;
    int velocidade;
    int x, y;
    //add uma que diz a direção caso queira fazer animação com sprite
    int bombas;
    int cooldownbomba;
    //renovar a bomba a cada tantos segundos, como fazer?
    }jogador;

    jogador pedro;
    
}
BeginDrawing();

//ele anda de acordo com as teclas

//ele anda x pixeis de acordo com a tecla pressionada

//ele verifica se não bateu numa parede

//ele tem velocidade, vida, nome