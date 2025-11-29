#include <iostream>
#include "terreno/terreno.h"

using namespace std;

int main(){
    string nomeArquivoPaleta;
    string nomeArquivoSaidaMapa;
    int tamanhoMapa;

    cout <<"Informe o nome do arquivo contendo a paleta de 10 cores:\n";
    cin>> nomeArquivoPaleta;

    cout <<"Informe o tamanho do mapa hipsometrico:\n";
    cin >> tamanhoMapa;

    cout<<"Informe o nome desejado para o arquivo da imagem do mapa:\n";
    cin >> nomeArquivoSaidaMapa;

    Terreno terreno(tamanhoMapa);
    terreno.gerarMapa(tamanhoMapa, 0.5);

    return 0;
}