##Mini bomberman em C
Este é um clone do clássico jogo Bomberman, desenvolvido em C com o auxílio da biblioteca Raylib. 

Requisitos

Para compilar e executar este projeto, irá precisar de:

    Um compilador C (como o GCC).

    A biblioteca Raylib.

    CMake para gerir o processo de compilação.

Como Compilar e Executar

Este projeto utiliza o CMake para facilitar a compilação em diferentes sistemas operativos.

    Clone o repositório:
    Bash

git clone [https://github.com/pedrofoletto/bomberman.git]
cd [bomberman]

Use o CMake para criar os ficheiros de compilação:
Bash

mkdir build
cd build
cmake ..

Compile o jogo:
Bash

make

Execute o jogo:
O executável será criado dentro da pasta build.
Bash

    ./main 

    (No Windows, o executável poderá chamar-se main.exe).

Controles do Jogo

    Movimento: Teclas W, A, S, D.

    Colocar Bomba: Barra de Espaço.

    Navegação no Menu: Setas Direcionais e Enter.

    Pausa: Tecla ESC durante o jogo.


Como Usar Mapas Personalizados

O jogo inclui uma ferramenta para converter mapas de texto em mapas que o jogo pode usar.

    Desenhe o seu mapa: Crie um ficheiro .txt na pasta maps/. Use 'W' para paredes, 'B' para tijolos destrutíveis e espaço para caminhos livres.

    Compile a ferramenta de conversão:
    Bash

cd tools
make conversao

Execute a conversão:
A ferramenta recebe o arquivo do mapa de entrada e o de saída como argumentos.
Bash

./conversao ../maps/meu_mapa.txt ../maps/custom_map.bin

Carregue no jogo: No menu de Opções do jogo, pressione a tecla L para carregar o custom_map.bin.