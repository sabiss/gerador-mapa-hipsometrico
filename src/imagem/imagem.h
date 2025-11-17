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

        int obterLargura(const Pixel& pixel) const;
        int obterAltura(const Pixel& pixel) const;
        bool lerPPM(const std::string filename);
        bool salvarPPM(const std::string filename);
};

#endif
