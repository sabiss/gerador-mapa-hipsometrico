#include "paleta.h"

Paleta::Paleta() {
    quantidade = 0;
}

Paleta::Paleta(const std::string filename) {
    lerArquivo(filename);
}

void Paleta::lerArquivo(const std::string filename){
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    quantidade = 0;

    std::string corHexa;
    while (file >> corHexa) {
        Cor cor = lerCorHex(corHexa);
        cores.adicionar(cor);
        quantidade++;
    }
}
void Paleta::adicionarCor(const Cor& cor) {
    cores.adicionar(cor);
    quantidade++;
}

int Paleta::obterTamanho() const {
    return quantidade;
}

Cor Paleta::obterCor(int id) const {
    if (id < 0 || id >= quantidade) {
        return Cor{0, 0, 0};
    }

    return cores[id];
}

int Paleta::hexChar(char caractere) {
    if (caractere >= '0' && caractere <= '9') {
        return caractere - '0';
    } 
    
    switch (caractere) {
    case 'a': case 'A': return a;
    case 'b': case 'B': return b;
    case 'c': case 'C': return c;
    case 'd': case 'D': return d;
    case 'e': case 'E': return e;
    case 'f': case 'F': return f;
    }

    return 0;
}

int Paleta::lerDuplaHex(const std::string& s, int i) {
    return hexChar(s[i]) * 16 + hexChar(s[i + 1]);
}

Cor Paleta::lerCorHex(const std::string& linha) {
    std::string hex = linha;
    if (hex[0] == '#'){
        hex = hex.substr(1);
    }

    Cor cor;
    cor.r = lerDuplaHex(hex, 0);
    cor.g = lerDuplaHex(hex, 2);
    cor.b = lerDuplaHex(hex, 4);

    return cor;
}
