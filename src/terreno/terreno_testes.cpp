#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "terreno.h"

// Você precisará criar testes adicionais para cobrir os métodos privados da classe.
// Por exemplo, você pode criar testes para os métodos das etapas Square e Diamond
// Você pode torná-los públicos temporariamente para fins de teste ou usar técnicas como "friend testing"

TEST_CASE("Testa a criação de um terreno") {//mudei por que não fazia sentido a criação de um terreno de uma célula só, pois não haverá diamond nem square
  Terreno terreno(0); // 2^0 + 1 = 2
  // CHECK(terreno.obterLargura() == 1);
  CHECK(terreno.obterProfundidade() == 2);
}

TEST_CASE("Testa a geração aleatória de altitudes") {
  Terreno terreno(2);
  // CHECK(terreno.obterLargura() == 5);
  CHECK(terreno.obterProfundidade() == 5);
  CHECK(terreno.obterAltitude(0, 0) == 0.0f); // Valor inicial
}

TEST_CASE("Testa cálculo de dimensão") {
    Terreno terreno(0);
    
    CHECK(terreno.calcularDimensao(0) == 2);  // 2^0 + 1 = 2
    CHECK(terreno.calcularDimensao(1) == 3);  // 2^1 + 1 = 3
    CHECK(terreno.calcularDimensao(2) == 5);  // 2^2 + 1 = 5
    CHECK(terreno.calcularDimensao(3) == 9);  // 2^3 + 1 = 9
    CHECK(terreno.calcularDimensao(4) == 17); // 2^4 + 1 = 17
}

TEST_CASE("Testa inicialização dos extremos") {
    Terreno terreno(2); // 5x5
    terreno.gerarMapa(2, 0.5f);
    
    // Verifica se os 4 cantos foram inicializados (não são mais zero)
    CHECK(terreno.obterAltitude(0, 0) != 0.0f);
    CHECK(terreno.obterAltitude(4, 0) != 0.0f);
    CHECK(terreno.obterAltitude(4, 4) != 0.0f);
    CHECK(terreno.obterAltitude(0, 4) != 0.0f);
}

TEST_CASE("Testa etapa Diamond - Pontos Centrais") {
    SUBCASE("Diamond em matriz 3x3") {
        Terreno terreno(1); // 3x3
        terreno.inicializarExtremos(10.0f);

        // Centro deve ser média dos 4 cantos + deslocamento
        float mediaEsperada = (terreno.obterAltitude(0, 0) + 
                              terreno.obterAltitude(0, 2) + 
                              terreno.obterAltitude(2, 0) + 
                              terreno.obterAltitude(2, 2)) / 4.0f;
        
         terreno.diamond(2, 5.0f);
         CHECK(terreno.obterAltitude(1, 1) != 0.0f);//calculou o centro
    
        float diferenca = std::abs(terreno.obterAltitude(1, 1) - mediaEsperada);//pego o centro e diminuo da média, para assim pegar o deslocamento aleatório que, se a conta da média dos pontos estiver certa, me retornará exatamente ele
        CHECK(diferenca <= 5.0f); // Diferença deve ser ≤ 5.0
    }
}
TEST_CASE("Teste Square - Valores Fixos Sem Aleatoriedade") {
    Terreno terreno(1);
    
    // Configura valores manualmente nos pontos conhecidos
    terreno.setAltitude(0, 0, 10.0f); // canto superior esquerdo
    terreno.setAltitude(0, 2, 20.0f); // canto superior direito  
    terreno.setAltitude(2, 0, 30.0f); // canto inferior esquerdo
    terreno.setAltitude(2, 2, 40.0f); // canto inferior direito
    terreno.setAltitude(1, 1, 25.0f); // centro
    
    terreno.square(2, 0.0f); // passo = 2, meio = 1, amplitude zero pra não alterar os calculos
    
    CHECK(terreno.obterAltitude(0, 1) == doctest::Approx(18.3333f)); // (10 + 20 + 25)/3 = 55/3
    CHECK(terreno.obterAltitude(1, 0) == doctest::Approx(21.6667f)); // (10 + 30 + 25)/3 = 65/3  
    CHECK(terreno.obterAltitude(1, 2) == doctest::Approx(28.3333f)); // (20 + 40 + 25)/3 = 85/3
    CHECK(terreno.obterAltitude(2, 1) == doctest::Approx(31.6667f)); // (30 + 40 + 25)/3 = 95/3
}

TEST_CASE("Testa se salvarMatriz salva o arquivo corretamente") {
    Terreno terreno(2); // matriz 5x5
    terreno.setAltitude(0, 0, 1.0f);
    terreno.setAltitude(0, 1, 2.0f);
    terreno.setAltitude(0, 2, 3.0f);
    terreno.setAltitude(0, 3, 4.0f);
    terreno.setAltitude(0, 4, 5.0f);

    std::string filename = "teste_salvar.txt";

    CHECK(terreno.salvarMatriz(filename) == true);

    std::ifstream f(filename);
    CHECK(f.is_open() == true);

    float v1, v2;
    f >> v1;
    f >> v2;

    CHECK(v1 == doctest::Approx(1.0f));
    CHECK(v2 == doctest::Approx(2.0f));
}

TEST_CASE("Testa se lerMatriz carrega valores corretos") {
    std::string filename = "teste_entrada.txt";

    {
        std::ofstream file(filename);
        for (int i = 0; i < 25; i++) {
            file << i * 1.5f << "\n";
        }
    }

    Terreno terreno(2);

    std::ifstream file(filename);
    CHECK(file.is_open() == true);

    CHECK(terreno.lerMatriz(file) == true);

    CHECK(terreno.obterAltitude(0,0) == doctest::Approx(0.0f));
    CHECK(terreno.obterAltitude(0,1) == doctest::Approx(1.5f));
    CHECK(terreno.obterAltitude(2,2) == doctest::Approx(1.5f * 12));
    CHECK(terreno.obterAltitude(4,4) == doctest::Approx(1.5f * 24));
}

TEST_CASE("Testa salvar e ler mantendo integridade da matriz") {
    Terreno original(2);

    float contador = 0.0f;
    for (int i = 0; i < original.obterProfundidade(); i++) {
        for (int j = 0; j < original.obterProfundidade(); j++) {
            original.setAltitude(i, j, contador);
            contador += 1.0f;
        }
    }

    std::string filename = "teste_integridade.txt";
    CHECK(original.salvarMatriz(filename) == true);

    Terreno carregado(2);
    std::ifstream file(filename);
    CHECK(file.is_open() == true);

    CHECK(carregado.lerMatriz(file) == true);

    // Comparar matriz inteira
    for (int i = 0; i < original.obterProfundidade(); i++) {
        for (int j = 0; j < original.obterProfundidade(); j++) {
            CHECK(original.obterAltitude(i,j) ==
                  doctest::Approx(carregado.obterAltitude(i,j)));
        }
    }
}
