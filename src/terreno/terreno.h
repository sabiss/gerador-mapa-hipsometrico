#include "paleta.h"
#include "imagem.h"
#ifndef TERRENO_H
#define TERRENO_H

class Terreno{
    float **altitudes;
    int dimensaoMatriz;

public:
    Terreno(int dimensao);
    ~Terreno();
    void gerarMapa(float fatorRugosidade);
    Imagem gerarImagem(Paleta paleta);
    float obterAltitude(int linha, int coluna) const;
    int obterProfundidade() const;//linhas
    int obterLargura(); 
    bool salvarMatriz();
    bool lerAlitudesDeArquivo();
    bool lerMatriz();
    void sombrear(Imagem& imagem);

private:
    int calcularDimensao(int valorDimensao);
    float gerarNumeroAleatorio(float amplitude);
    void inicializarExtremos(float amplitude);
    void diamond(int passo, float deslocamentoAleatorio);
    void square(int passo, float amplitude);
    void setAltitude(int linha, int coluna, float valor);
    void colorirImagem(Paleta paletaCores, Imagem& imagem);
};

#endif