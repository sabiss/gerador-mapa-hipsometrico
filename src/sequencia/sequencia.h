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
        
    private:
        void aumentarCapacidade(){
            capacidade*=2;
            T *novaSequencia = new T[capacidade];//crio um novo espaço na memória com a capacidade nova

            for(int i = 0; i < quantDados; i++){//passo todos os dados já cadastrado pra ela
                novaS
                equencia[i] = dados[i];
            }
            delete[] dados;//limpo aquela memoria reservada;
            dados = novaSequencia;//agora o array de dados apontar pra essa nova Sequencia de capacidade maior;
        }
};