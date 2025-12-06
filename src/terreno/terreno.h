#include "../paleta/paleta.h"
#include "../imagem/imagem.h"
#ifndef TERRENO_H
#define TERRENO_H

class Terreno{
    float **altitudes;
    int dimensaoMatriz;

public:
    Terreno(int dimensao);
    ~Terreno();
    float& operator()(int i, int j);
    const float& operator()(int i, int j) const;
    void gerarMapa(int tamanhoMatriz, float fatorRugosidade);
    void gerarMapa(float fatorRugosidade);
    Imagem gerarImagem(Paleta paleta);
    float obterAltitude(int linha, int coluna) const;
    int obterProfundidade() const;//linhas
    int obterLargura(); 
    bool salvarMatriz(const std::string& filename);
    bool lerMatriz(std::ifstream &file);
    void sombrear(Imagem& imagem);
    bool salvarMatriz();
    bool lerAlitudesDeArquivo();
    bool lerMatriz();
    

public:
    bool destrutorTerreno();
    bool escreverMatriz(std::ofstream &file);
    int calcularDimensao(int valorDimensao);
    float gerarNumeroAleatorio(float amplitude);
    void inicializarExtremos(float amplitude);
    void diamond(int passo, float deslocamentoAleatorio);
    void square(int passo, float amplitude);
    void setAltitude(int linha, int coluna, float valor);
    void colorirImagem(Paleta paletaCores, Imagem& imagem);
};

#endif