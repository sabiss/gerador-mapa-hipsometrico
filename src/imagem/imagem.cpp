#include "imagem.h"

Imagem::Imagem(){
    altura = 0;
    largura = 0;
    pixels = nullptr;
}

Imagem::Imagem(int lar, int alt){
    altura = alt;
    largura = lar;
    pixels = new Pixel*[altura];

    for(int i = 0; i < altura; i++){
        pixels[i] = new Pixel[largura];
    }

    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            pixels[i][j] = {0, 0, 0};
        }
    }
}

Imagem::~Imagem(){
    for(int i = 0; i < altura; i++){
        delete[] pixels[i];
    }

    delete[] pixels;
}

Pixel& Imagem::operator()(int i, int j) {
    return pixels[j][i];
}

const Pixel& Imagem::operator()(int i, int j) const {
    return pixels[j][i];
}

int Imagem::obterLargura() const{
    return largura;
}
    
int Imagem::obterAltura() const{
    return altura;
}

bool Imagem::lerPPM(const std::string filename){
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    if (!lerCabecalho(file)) return false;
    if (!lerPixels(file)) return false;

    return true;
}

bool Imagem::salvarPPM(const std::string filename){
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    if (!escreverCabecalho(file)) return false;
    if (!escreverPixels(file)) return false;

    return true;
}

bool Imagem::lerCabecalho(std::ifstream &file){
    std::string identificador;
    file >> identificador;

    if(identificador != "P3") return false;

    file >> largura >> altura;

    int valorMaximo;
    file >> valorMaximo;

    return true;
}

bool Imagem::lerPixels(std::ifstream &file){
    Pixel **pixelsLidos = new Pixel*[altura];

    for(int i = 0; i < altura; i++){
        pixelsLidos[i] = new Pixel[largura];
    }

    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            int r, g, b;
            file >> r >> g >> b;
            pixelsLidos[i][j] = {r, g, b};
        }
    }
    delete [] pixels;
    pixels = pixelsLidos;

    return true;
}

bool Imagem::escreverCabecalho(std::ofstream &file) {
    file << "P3" << std::endl;
    file << largura << " " << altura << std::endl;
    file << "255" << std::endl;

    return true;
}

bool Imagem::escreverPixels(std::ofstream &file) {
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            Pixel& p = (*this)(j, i);
            file << p.r << " " << p.g << " " << p.b << std::endl;
        }
    }

    return true;
}

