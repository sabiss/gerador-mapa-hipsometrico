#ifndef TERRENO_H
#define TERRENO_H

class Terreno{
    float **altitudes;
    int dimensaoMatriz;

public:
    Terreno(int dimensao);
    ~Terreno();
    void gerarMapa(int tamanhoMatriz, float fatorRugosidade);
    float consultarAltitude(int linha, int coluna);
    int obterProfundidade();
    int obterLargura();
    bool salvarMatriz();
    bool lerAlitudesDeArquivo();

private:
    int calcularDimensao(int valorDimensao);
    float gerarNumeroAleatorio(float amplitude);
    void inicializarExtremos(float amplitude);
};

#endif