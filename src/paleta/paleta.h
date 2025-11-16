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
    int getNumeroCor() const;
    Cor getCorPorId(int id) const;

private:
    enum hexas {
        a = 10, b, c, d, e, f
    };

    int hexChar(char caractere);
    int lerDuplaHex(const std::string& s, int i);
    Cor lerCorHex(const std::string& linha);
};

#endif
