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

int Terreno::calcularDimensao(int valorDimensao){
    return (pow(2, valorDimensao)+1);
};

void Terreno::inicializarExtremos(float amplitude){
    altitudes[0][0] = gerarNumeroAleatorio(amplitude);
    altitudes[0][dimensaoMatriz-1] = gerarNumeroAleatorio(amplitude);
    altitudes[dimensaoMatriz-1][0] = gerarNumeroAleatorio(amplitude);
    altitudes[dimensaoMatriz-1][dimensaoMatriz-1] = gerarNumeroAleatorio(amplitude);
};

float Terreno::gerarNumeroAleatorio(float amplitude){
    return (rand() / (float)RAND_MAX) * amplitude;  // 0.0 a amplitude
}
