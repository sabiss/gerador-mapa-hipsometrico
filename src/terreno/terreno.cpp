#include "terreno.h"
#include <cmath>//biblioteca do pow

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
