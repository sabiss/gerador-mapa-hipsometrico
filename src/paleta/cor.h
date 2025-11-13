#include <iostream>

class Cor{
    int R;
    int G;
    int B;

    public:
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
        }
};