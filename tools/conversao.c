#include <stdio.h>
#include <stdlib.h>

#define ALTURA 15
#define LARGURA 15

//converte o arquivo txt do professor para a minha matriz int
int Conversao(char c) {
    switch (c) {
        case 'w': return 1; // parede
        case 'b': return 2; // tijolo
        case ' ': return 0; // vazio
        default: return 0;  // trata qualquer outro como vazio
    }
}

int main (int argc, char *argv[]){ //argc = contagem de argumentos, argv = valores dos argumentos
    //argc = 3 palavras no comando
    //argv 0 ./conversao | argv1 maps/mapadosor.txt | argv2 maps/custom_map.bin
    if (argc != 3){
        printf("Uso: %s <arquivo_de_entrada.txt> <arquivo_de_saida.bin>\n", argv[0]);
        return 1;
    }
    FILE *inputfile = fopen(argv[1], "r"); //maps/mapadosor.txt
    if (inputfile == NULL){
        perror("erro ao abrir o mapa enviado");
        return 1;
    }
    FILE *outputfile = fopen(argv[2], "wb"); //maps/custom_map.bin
    if(outputfile == NULL){
        perror("Erro ao abrir arquivo de saída");
        fclose(inputfile);
        return 1;
    }

    int mapa[ALTURA][LARGURA];
    char caracter;
    printf("convertendo \n");
        
    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            // fgetc lê um caractere do arquivo
            caracter = fgetc(inputfile);
            // Ignora quebras de linha e outros caracteres indesejados
            while (caracter == '\n' || caracter == '\r') {
                caracter = fgetc(inputfile);
            }
            if (caracter == EOF) { // EOF é o \0 do file
                mapa[y][x] = 0;
            } else {
                mapa[y][x] = Conversao(caracter);
            }
        }
    }
    // escreve no arquivo binário
    fwrite(mapa, sizeof(int), ALTURA * LARGURA, outputfile);
    fclose(inputfile);
    fclose(outputfile);

    printf("Mapa '%s' convertido com sucesso para '%s'\n", argv[1], argv[2]);

    return 0;
}