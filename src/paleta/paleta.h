#include "../sequencia/sequencia.h"
#include "cor.h"
#include <iostream>
#include <fstream>

class Paleta{
    int quantidade;
    Sequencia<Cor> cores;

    private:
        enum hexas {
            a = 10, b, c, d, e, f
        };

        int hexChar(char caractere) {
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

        int lerDuplaHex(const std::string& s, int i) {
            return hexChar(s[i]) * 16 + hexChar(s[i + 1]);
        }

        Cor lerCorHex(const std::string& linha) {
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

    public:
        Paleta() {
            quantidade = 0;
        }

        Paleta(const std::string filename) {
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
};
