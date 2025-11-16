#include <iostream>

struct Cor{
    int r;
    int g;
    int b;

    //Validação das cores caso testes fossem feitos com outros arquivos não formatados
    /*public:
        Cor(int vermelho=0, int verde=0, int azul=0){
            R = validarHex(vermelho);//para caso o usuário insira uma cor maior que o limite(255) do RGB
            G = validarHex(verde);
            B = validarHex(azul);
        }
    private:
        int validarHex(int valor){
            if(valor > 255){
                return 255;
            }else if(valor < 0){
                return 0;
            }else{
                return valor;
            }
        }*/
};