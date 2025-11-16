#include "paleta.h";

Paleta::Paleta() {
        quantidade = 0;
}

Paleta::Paleta(const std::string filename) {
    quantidade = 0;
    std::ifstream file(filename);

    if (!file.is_open()) return;

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
    return cores[id];
}

int Paleta::hexChar(char caractere) {
    if (caractere >= '0' && caractere <= '9') {
        return caractere - '0';
    } 
    
    // É necessário validar se o caractere é uma letra minúscula?
    switch (caractere) {
    case 'a': return a;
    case 'b': return b;
    case 'c': return c;
    case 'd': return d;
    case 'e': return e;
    case 'f': return f;
    }
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
    cor.R = lerDuplaHex(hex, 0);
    cor.G = lerDuplaHex(hex, 2);
    cor.B = lerDuplaHex(hex, 4);

    return cor;
}
