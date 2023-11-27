#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <algorithm>
#include <set>
#include <bitset>
#include <iomanip>
#include <math.h>
#include <queue>
#include <cstdio>

using namespace std;

struct Secao {
    long long int bonificacao;
    long long int tempoDeTravessia;
};

struct Pista {
    vector<Secao> secoes;
};

struct Manobra {
    long long int duracao;
    long long int pontuacaoBase; //pode ser negativa
};

vector<int> getManobrasSelecionadas(vector<bool> &manobras) {
    vector<int> result;
    for(int i = 0; i < manobras.size(); i++) {
        if(manobras[i]) result.push_back(i);
    }
    return result;
}

void limparManobras(vector<bool> &vec) {
    for (long long int i = 0; i < vec.size(); i++) {
        vec[i] = false;
    }
}

// int knapSackRecursivo(long long int index, long long int capacidade, vector<Manobra>& manobras, vector<vector<long long int>> & auxMatrix) {
//     int resultFinal;
//     if(auxMatrix[index][capacidade] != 0) return auxMatrix[index][capacidade];
//     if(capacidade == 0 || index == 0) {
//         resultFinal = 0;
//     } else if (manobras[index].duracao > capacidade) {
//         resultFinal = knapSackRecursivo(index - 1, capacidade, manobras, auxMatrix);
//     } else {
//         int result1 = knapSackRecursivo(index - 1, capacidade, manobras, auxMatrix);
//         int result2 = manobras[index].pontuacaoBase + knapSackRecursivo(index - 1, capacidade - manobras[index].duracao, manobras, auxMatrix);
//         resultFinal = max(result1, result2);
//     }
//     auxMatrix[index][capacidade] = resultFinal;
//     return resultFinal;
// }

void imprimirMatriz(vector<vector<long long int>> &matriz, int LINHAS, int COLUNAS) {
    // Imprime os índices das colunas em binário
    cout << setw(5) << " ";
    for (int j = 0; j < COLUNAS; ++j) {
        cout << setw(9) << bitset<4>(j); // 4 bits para representar números até 3 (binário: 11)
    }
    cout << endl;

    for (int i = 0; i < LINHAS; ++i) {
        // Imprime o índice da linha em binário
        cout << bitset<4>(i) << " ";

        for (int j = 0; j < COLUNAS; ++j) {
            cout << setw(9) << matriz[i][j];
        }
        cout << endl;
    }
}

void knapSack(Secao &secao, vector<Manobra>& manobras, vector<bool>&manobrasCheck) {
    //Bottom up -> começo achando a solução otima para da menor capacidade até chegar na maior capacidade
    long long int numTempoTravessia = secao.tempoDeTravessia;
    const long int numManobras = manobras.size();

    vector<vector<long long int>> K(numManobras + 1, vector<long long int>(numTempoTravessia + 1));

    for (long long int i = 0; i <= numManobras; i++) {
        for (long long int w = 0; w <= numTempoTravessia; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            } else if (manobras[i - 1].duracao <= w) {
                K[i][w] = max(manobras[i - 1].pontuacaoBase + K[i - 1][w - manobras[i - 1].duracao], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    long long int res = K[numManobras][numTempoTravessia];
    long long int auxValue = res;
    
    long long int tempoUsado = numTempoTravessia;
    vector<long long int> manobrasSelecionadas;

    for (long long int i = numManobras; i > 0 && auxValue > 0; i--) {
        if (auxValue != K[i - 1][tempoUsado]) {
            manobrasSelecionadas.push_back(i - 1);
            auxValue -= manobras[i - 1].pontuacaoBase;
            tempoUsado -= manobras[i - 1].duracao;
        }
    }

    cout << "Índices das manobras selecionadas: ";
    for (long long int i = manobrasSelecionadas.size() - 1; i >= 0; i--) {
        cout << manobrasSelecionadas[i] << " ";
    }
    cout << endl;

    cout << "Valor máximo obtido como bonus: " << res * secao.bonificacao * manobrasSelecionadas.size() << endl;

    cout << endl;
}

int main() {
    Pista pista;
    vector<Manobra> manobras;
    long long int numSecoes, numManobras;

    scanf("%lld %lld", &numSecoes, &numManobras);

    for (long long int i = 0; i < numSecoes; i++) {
        long long int bonificacao, tempoTravessia;
        
        scanf("%lld %lld", &bonificacao, &tempoTravessia);

        Secao newSecao;
        newSecao.bonificacao = bonificacao;
        newSecao.tempoDeTravessia = tempoTravessia;

        pista.secoes.push_back(newSecao);
    }

    for (long long int i = 0; i < numManobras; i++) {
        long long int pontuacaoBase, duracao;
        
        scanf("%lld %lld", &pontuacaoBase, &duracao);

        Manobra newManobra;
        newManobra.pontuacaoBase = pontuacaoBase;
        newManobra.duracao = duracao;

        manobras.push_back(newManobra);
    }

    vector<bool> manobrasCheck(numManobras, false);

    //Criar um vetor do tamanho de numManobras de booleano
    //Assim que eu resolver uma mochila eu marco nesse vetor quais foram as manobras usadas na ultima seção e passo esse vetor para a próxima seção,
    //Ai la dentro do knapSack eu trato pra ver se a manobra que eu to escolhendo agora ja foi usada na ultima seção
    //Mano, depois de rodar pra cada seção eu tenho os resultados

    //matriz 1024 (2^10), a linha é a config que eu fiz antes, ex pra 3 manobras (010) e a coluna é a config que eu to fazendo agora, ex (110)

    vector<vector<long long int>> manobrasPreCalc(pow(2, numManobras), vector<long long int>(pow(2, numManobras)));

    for(int i = 0; i < pow(2, numManobras); i++) {
        for(int j = 0; j < pow(2, numManobras); j++){
            int sum = 0;
            for(int h = 0; h < numManobras; h++) {
                int bitHdej = (j >> h) & 1;
                int bitHdei = (i >> h) & 1;

                if(bitHdej == 1 && bitHdei == 1) {
                    sum += manobras[h].pontuacaoBase / 2;
                } else if (bitHdej == 1 && bitHdei == 0) {
                    sum += manobras[h].pontuacaoBase;
                }
            }
            manobrasPreCalc[i][j] = sum;
        }
    }

    imprimirMatriz(manobrasPreCalc, pow(2, numManobras), pow(2, numManobras));

    // for(long long int i = 0; i < numSecoes; i++) {
    //     limparManobras(manobrasCheck);
    //     knapSack(pista.secoes[i], manobras, manobrasCheck);
    //     vector<int> selectedManobras = getManobrasSelecionadas(manobrasCheck);
    // }

    cout << "----------------------------------------" << endl;

    // for(long long int i = 0; i < numSecoes; i++) {
        
    //     vector<vector<long long int>> K(numManobras + 1, vector<long long int>(pista.secoes[i].tempoDeTravessia + 1));
    //     int result = knapSackRecursivo(manobras.size() - 1, pista.secoes[i].tempoDeTravessia, manobras, K);
    //     cout << "Valor máximo obtido: " << result * pista.secoes[i].bonificacao << endl;
    //     // if(counter % 2 == 0) {
    //     //     knapSack(pista.secoes[i], manobras, manobrasCheck);
    //     // }
    // }
}

//cada mochila é uma seção, cada mochila eu tenho que retornar os pontos que eu faço na seção e quais manobras eu usei,
//peso do item é o tempo de exec da manobra e o lucro do item é os pontos da manobra