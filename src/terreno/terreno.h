#ifndef TERRENO_H
#define TERRENO_H

class Terreno{
    float **altitudes;
    int dimensaoMatriz;

public:
    Terreno(int dimensao);
    ~Terreno();
    void gerarMapa(int tamanhoMatriz, float fatorRugosidade);
    float obterAltitude(int linha, int coluna) const;
    int obterProfundidade() const;//linhas
    int obterLargura();
    bool salvarMatriz();
    bool lerAlitudesDeArquivo();
    bool lerMatriz();

private:
    int calcularDimensao(int valorDimensao);
    float gerarNumeroAleatorio(float amplitude);
    void inicializarExtremos(float amplitude);
    void diamond(int passo, float deslocamentoAleatorio);
    void square(int passo, float amplitude);
    void setAltitude(int linha, int coluna, float valor);
};

#endif