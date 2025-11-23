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

void Terreno::gerarMapa(int n, float rugosidade) {
    int tamanho = calcularDimensao(n);
    float amplitude = 10.0f;
    
    srand(time(0));
    inicializarExtremos(amplitude);
    
    int passo = tamanho - 1;//passo vai ser a etapa, o quadrado em questão | Passo 5 = Quaddrado 5x5
    float amplitudeAtual = amplitude;
    
    while (passo >= 2) {
        diamond(passo, amplitudeAtual);
        square(passo, amplitudeAtual);
        
        amplitudeAtual *= rugosidade;
        passo /= 2;
    }
};

int Terreno::calcularDimensao(int n){
    return static_cast<int>(std::pow(2, n)) + 1; //a pow retorna um double, mas a dimensao tem que ser int, então converto ela com um cast
}

float Terreno::obterAltitude(int linha, int coluna)const{
    return altitudes[linha][coluna];
}

int Terreno::obterProfundidade() const{
    return dimensaoMatriz;
}

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

void Terreno::square(int passo, float amplitude){
    int meio = passo / 2;
    
    for(int x = 0; x < dimensaoMatriz; x += meio){
        for(int y = 0; y < dimensaoMatriz; y += meio){
            if((x % passo == 0 && y % passo == meio) ||  // Pontos verticais
               (x % passo == meio && y % passo == 0)) {  // Pontos horizontais
                //todos os pontos são multiplos do passo(Quadrado em questão)
                if(altitudes[x][y] == 0.0f) {//se ainda não preencher, pra n correr o risco de sobreescrever
                    float somatorio = 0.0f;
                    //apesar de ser sempre 3 pontos, precisa de 4 ifs pois, em algumas configurações vai haver ponto Direita, Esquerda, Acima mas em outros Direita, Esquerda e Abaxio como em 9x9 no ponto (8,4) que é o resultado do square D, E, Acima
                    if(x - meio >= 0) {
                        somatorio += altitudes[x - meio][y]; // acima
                    }
                    if(x + meio < dimensaoMatriz) {
                        somatorio += altitudes[x + meio][y]; // abaixo
                    }
                    if(y - meio >= 0) {
                        somatorio += altitudes[x][y - meio]; // esquerda
                    }
                    if(y + meio < dimensaoMatriz) {
                        somatorio += altitudes[x][y + meio]; // direita
                    }
                    
                    altitudes[x][y] = (somatorio / 3.0f) + gerarNumeroAleatorio(amplitude);
                }
            }
        }
    }
};

float Terreno::gerarNumeroAleatorio(float amplitude) {
    return ((rand() / (float)RAND_MAX) * 2.0f - 1.0f) * amplitude;
}

void Terreno::setAltitude(int linha, int coluna, float valor){
    altitudes[linha][coluna] = valor;
}

