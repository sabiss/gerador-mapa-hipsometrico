#ifndef IMAGEM_H
#define IMAGEM_H

#include <iostream>
#include <fstream>
#include "./pixel.h"

class Imagem{
    int largura;
    int altura;
    Pixel **pixels;

public:
    Imagem();
    Imagem(int lar, int alt);
    ~Imagem();

    Pixel& operator()(int i, int j);
    const Pixel& operator()(int i, int j) const;

    int obterLargura() const;
    int obterAltura() const;

    bool lerPPM(const std::string filename);
    bool salvarPPM(const std::string filename);

private:
    bool lerCabecalho(std::ifstream &file);
    bool lerPixels(std::ifstream &file);
    bool escreverCabecalho(std::ofstream &file);
    bool escreverPixels(std::ofstream &file);
};

#endif
