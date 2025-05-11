cc game.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./a.out

gcc -o bomberman game.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 ./bomberman

cc testeraylib.c -o testeraylib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

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
            //srand(time(NULL)); (ele pode ser executado só uma vez?)
            for(int i = 0; i < 10; i++){ //10 máx inimigos
                int chanceatual = chancesaida + 10 * mortos; //aumenta chance da segunda saída
                int talvezsaida = rand() % 100;
    
                if (talvezsaida < chanceatual){
                //criar saída
                }  
            }
        }
    }