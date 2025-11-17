#ifndef IMAGEM_H
#define IMAGEM_H

#include <iostream>
#include "./pixel.h"
#include "../sequencia/sequencia.h"

class Imagem{
    int largura;
    int altura;
    Cor **pixels;

    public:
        Imagem(int lar, int alt);
        ~Imagem();
};

#endif
