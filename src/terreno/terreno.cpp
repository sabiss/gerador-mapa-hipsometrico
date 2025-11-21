#include "terreno.h"
#include <cmath>//biblioteca do pow
#include <cstdlib>//biblioteca do gerador de n° aleatório
#include <ctime>//biblioteca do gerador de n° aleatório

Terreno::Terreno(int dimensao=3) {
    dimensaoMatriz = calcularDimensao(dimensao);

    altitudes = new float*[dimensaoMatriz];
    for(int linha = 0; linha < dimensaoMatriz; linha++){
        altitudes[linha] = new float[dimensaoMatriz];
        for(int coluna = 0; coluna < dimensaoMatriz; coluna++){
            altitudes[linha][coluna] = 0.0f;
        }
    }
};

Terreno::~Terreno(){
    for(int linha = 0; linha < dimensaoMatriz; linha++){
        delete[] altitudes[linha];
    }
    delete[] altitudes;
    altitudes = nullptr;
}

void Terreno::gerarMapa(int dimensaoMatriz, float rugosidade){
    float amplitude = 10.0f;

    srand(time(0));//gerador de numeros
    inicializarExtremos(amplitude);
}

int Terreno::calcularDimensao(int valorDimensao){
    return (pow(2, valorDimensao)+1);
};

void Terreno::inicializarExtremos(float amplitude){
    altitudes[0][0] = gerarNumeroAleatorio(amplitude);
    altitudes[0][dimensaoMatriz-1] = gerarNumeroAleatorio(amplitude);
    altitudes[dimensaoMatriz-1][0] = gerarNumeroAleatorio(amplitude);
    altitudes[dimensaoMatriz-1][dimensaoMatriz-1] = gerarNumeroAleatorio(amplitude);
    
};
void Terreno::diamond(int passo, float amplitude) {
    int meioPasso = passo / 2;
    
    for(int x = meioPasso; x < dimensaoMatriz - 1; x += passo) {
        for(int y = meioPasso; y < dimensaoMatriz - 1; y += passo) {
            float media = (altitudes[x - meioPasso][y - meioPasso] +  // superior esquerdo
                          altitudes[x - meioPasso][y + meioPasso] +  // superior direito
                          altitudes[x + meioPasso][y - meioPasso] +  // inferior esquerdo
                          altitudes[x + meioPasso][y + meioPasso]) / 4.0f;  // inferior direito
            
            altitudes[x][y] = media + gerarNumeroAleatorio(amplitude);
        }
    }
}

float Terreno::gerarNumeroAleatorio(float amplitude) {
    return ((rand() / (float)RAND_MAX) * 2.0f - 1.0f) * amplitude;
}
