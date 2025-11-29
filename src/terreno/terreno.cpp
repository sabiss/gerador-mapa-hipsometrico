#include "terreno.h"
#include "imagem.h"
#include "paleta.h"
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

void Terreno::gerarMapa(float rugosidade) {
    int tamanho = dimensaoMatriz;
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

Imagem Terreno::gerarImagem(Paleta paleta){
    Imagem imagemMapa(dimensaoMatriz, dimensaoMatriz);
    colorirImagem(paleta, imagemMapa);
    sombrear(imagemMapa);
    return imagemMapa;
}

void Terreno::colorirImagem(Paleta paletaCores, Imagem imagem){
    for(int linha = 0; linha < dimensaoMatriz; linha++){
        for(int coluna = 0; coluna < dimensaoMatriz; coluna++){
            float altitudeAtual = altitudes[linha][coluna];
            int cor = 0;

            if(altitudeAtual >=-10.0f && altitudeAtual <-8.0f){
                cor = 0;
            } else if(altitudeAtual >=-8.0f && altitudeAtual <-6.0f){
                cor = 1;
            } else if(altitudeAtual >=-6.0f && altitudeAtual <-4.0f){
                cor = 2;
            } else if(altitudeAtual >=-4.0f && altitudeAtual <-2.0f){
                cor = 3;
            } else if(altitudeAtual >=-2.0f && altitudeAtual <0.0f){
                cor = 4;
            }else if(altitudeAtual >=0.0f && altitudeAtual <2.0f){
                cor = 5;
            }else if(altitudeAtual >=2.0f && altitudeAtual <4.0f){
                cor = 6;
            }else if(altitudeAtual >=4.0f && altitudeAtual <6.0f){
                cor = 7;
            }else if(altitudeAtual >=6.0f && altitudeAtual <8.0f){
                cor = 8;
            }else if(altitudeAtual >=8.0f && altitudeAtual <=10.0f){
                cor = 9;
            }

            imagem(linha, coluna) = paletaCores.obterCor(cor);
        }
    }
}

void Terreno::sombrear(Imagem imagem){
    for(int x = 8; x > -1; x--){
        for(int y = 8; y > -1; y--){
            if( x - 1 > -1 && y - 1 > -1){//se o ponto da superior esquerdo existir
                if(altitudes[x][y] < altitudes[x-1][y-1]){
                    imagem(x, y).r = imagem(x, y).r * 0.5; 
                    imagem(x, y).g = imagem(x, y).g * 0.5;
                    imagem(x, y).b = imagem(x, y).b * 0.5;
                }
            }
        }
    }
}

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

