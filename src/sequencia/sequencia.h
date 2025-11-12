#include <iostream>

template <typename T>
class Sequencia{
    int capacidade;
    int quantDados;
    T *dados;

    public:
        Sequencia() {
            capacidade = 10;
            quantDados = 0;
            dados = new T[capacidade];//alocará um espaço de memório de tamanho da CAPACIDADE e o ponteiro dados apontará para ele
        }

        ~Sequencia(){//é preciso dizer ao pc "essa memória antes alocada com valores que quero guardar está livre pra você usar e substituir por algo novo"
            delete[] dados;
        }
};