#include <iostream>
#include "./pixel.h"
#include "../sequencia/sequencia.h"

class Imagem{
    int largura;
    int altura;
    Cor **pixels;

    public:
        Imagem(int lar, int alt){
            altura = alt;
            largura = lar;
            pixels = new Cor*[altura];

            for(int i = 0; i<altura; i++){
                pixels[i] = new Cor[largura];
            }

            for(int i = 0; i< altura; i++){
                for(int e = 0; e < largura; e++){
                    pixels[i][e] = {0,0,0};
                }
            }
        }
};
