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

    if (tamanhoMapa < 0) {
        while(true){
            cout << "ERRO: Tamanho deve ser entre 1 e 10\n";
            cout <<"Informe o tamanho do mapa hipsometrico:\n";
            cin >> tamanhoMapa;
            if(tamanhoMapa>0){break;}
        }
    }

    cout<<"Informe o nome desejado para o arquivo da imagem do mapa:\n";
    cin >> nomeArquivoSaidaMapa;

    Paleta paleta(nomeArquivoPaleta);
    
     while (paleta.obterTamanho() < 10) {
        paleta.destrutorSequencia();

        cout << "ERRO: Paleta precisa ter pelo menos 10 cores! E tem: " 
             << paleta.obterTamanho() << endl;
        cout <<"Informe o nome do arquivo contendo a paleta de pelo menos 10 cores:\n";
        cin>> nomeArquivoPaleta;
        
        paleta.lerArquivo(nomeArquivoPaleta);
    }
    Terreno terreno(tamanhoMapa);
    terreno.gerarMapa(0.5);
    Imagem imagemMapa = terreno.gerarImagem(paleta);
    imagemMapa.salvarPPM(nomeArquivoSaidaMapa);
    cout<<"A imagem do mapa hipsometrico foi criada";

    return 0;
}