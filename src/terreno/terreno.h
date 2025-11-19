#ifndef TERRENO_H
#define TERRENO_H

class Terreno{

public:
    Terreno(int dimensao);
    ~Terreno();
    void gerarMapa(int tamanhoMatriz, float fatorRugosidade);
    float consultarAltitude(int linha, int coluna);
    int obterProfundidade();
    int obterLargura();
    bool salvarMatriz();
    bool lerAlitudesDeArquivo();
};

#endif