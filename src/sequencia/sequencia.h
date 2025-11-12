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
        int getQuantDados(){
            return quantDados;
        }

        void adicionar(T novoElemento){
            if(quantDados>=capacidade){
                aumentarCapacidade();
            }
            dados[quantDados] = novoElemento;
            quantDados++;
        }
        void removerUltimoDado(){
            quantDados--;
        }

        T operator[](int index) const {//BUSCAR  | o const faz o retorno ser constante, logo, retorna uma cópia do tipo T, ou seja, não será possível editar o array assim
            if(index>=quantDados || index<0){//não há elemento armazenado nesse index ou index negativo
                std::cerr<<"Erro! Index inválido para capacidade do array";
            }
            return dados[index];
        }

        T& operator[](int index){//EDITAR  | &T por que retorna uma referência(&) a um tipo T
            if(index>=quantDados || index<0){//não há elemento armazenado nesse index ou index negativo
                std::cerr<<"Erro! Index inválido para capacidade do array";
            }
            return dados[index];//por causa do & retorna a referência, então é editável
        }
        // T buscarElementoViaIndex(int index){
        //     if(index>=quantDados || index<0){//não há elemento armazenado nesse index ou index negativo
        //         std::cerr<<"Erro! Index inválido para capacidade do array";
        //     }
        //     return dados[index];
        // }
        // void editarElementoViaIndex(int index, T novoElemento){
        //     dados[index] = novoElemento;
        // }
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