#ifndef PALETA_H
#define PALETA_H

#include "../sequencia/sequencia.h"
#include "cor.h"
#include <iostream>
#include <fstream>

class Paleta{
    int quantidade;
    Sequencia<Cor> cores;

public:
    Paleta();
    Paleta(const std::string filename);

    void adicionarCor(const Cor& cor);
    int obterTamanho() const;
    Cor obterCor(int id) const;
    void lerArquivo(const std::string filename);
    void destrutorSequencia();

private:
    enum hexas {
        a = 10, b, c, d, e, f
    };

    int hexChar(char caractere);
    int lerDuplaHex(const std::string& s, int i);
    Cor lerCorHex(const std::string& linha);
};

#endif
