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
#include <limits.h>

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

pair<long long int, vector<int>> knapSack(
    int currentSection, 
    int manobraAtual, 
    vector<Secao> &secoes, 
    vector<Manobra>& manobras, 
    vector<vector<long long int>>&preCalc, 
    vector<vector<pair<long long int, vector<int>>>>&matrizDP
) {
    if(currentSection >= secoes.size()) return make_pair(0, vector<int>());

    if(matrizDP[currentSection][manobraAtual].first != -LLONG_MAX) {
        return matrizDP[currentSection][manobraAtual];
    }

    long long int MaxPoints = 0;
    vector<int> manobrasUsadas;

    for(int proximaManobra = 0; proximaManobra < pow(2, manobras.size()); proximaManobra++) {
        int j = 0;
        int bitH = 0;
        long long int duracao = 0;

        while(j < manobras.size()) {
            bitH = (proximaManobra >> j) & 1;
            if(bitH) {
                duracao = duracao + manobras[j].duracao;
            }
            j++;
        }

        if(duracao > secoes[currentSection].tempoDeTravessia) {
            continue;
        }

        long long int pontosAcumulados = preCalc[manobraAtual][proximaManobra] * secoes[currentSection].bonificacao * __builtin_popcountll(proximaManobra);

        pair<long long int, vector<int>> result = knapSack(currentSection + 1, proximaManobra, secoes, manobras, preCalc, matrizDP);

        if(pontosAcumulados + result.first > MaxPoints) {
            MaxPoints = pontosAcumulados + result.first;
            manobrasUsadas = {proximaManobra};
            manobrasUsadas.insert(manobrasUsadas.end(), result.second.begin(), result.second.end());
        }
    }

    matrizDP[currentSection][manobraAtual].first = MaxPoints;
    matrizDP[currentSection][manobraAtual].second = manobrasUsadas;
    return matrizDP[currentSection][manobraAtual];
}

int main() {
    Pista pista;
    vector<Manobra> manobras;
    int numSecoes, numManobras;

    scanf("%d %d", &numSecoes, &numManobras);

    for (int i = 0; i < numSecoes; i++) {
        long long int bonificacao, tempoTravessia;
        
        scanf("%lld %lld", &bonificacao, &tempoTravessia);

        Secao newSecao;
        newSecao.bonificacao = bonificacao;
        newSecao.tempoDeTravessia = tempoTravessia;

        pista.secoes.push_back(newSecao);
    }

    for (int i = 0; i < numManobras; i++) {
        long long int pontuacaoBase, duracao;
        
        scanf("%lld %lld", &pontuacaoBase, &duracao);

        Manobra newManobra;
        newManobra.pontuacaoBase = pontuacaoBase;
        newManobra.duracao = duracao;

        manobras.push_back(newManobra);
    }

    vector<vector<long long int>> manobrasPreCalc(pow(2, numManobras), vector<long long int>(pow(2, numManobras)));

    for(int i = 0; i < pow(2, numManobras); i++) {
        for(int j = 0; j < pow(2, numManobras); j++){
            int sum = 0;
            for(int h = 0; h < numManobras; h++) {
                int bitHdej = (j >> h) & 1;
                int bitHdei = (i >> h) & 1;

                if(bitHdej == 1 && bitHdei == 1) {
                    sum += floor(manobras[h].pontuacaoBase / 2);
                } else if (bitHdej == 1 && bitHdei == 0) {
                    sum += manobras[h].pontuacaoBase;
                }
            }
            manobrasPreCalc[i][j] = sum;
        }
    }

    vector<vector<pair<long long int, vector<int>>>> MatrizDP(numSecoes, vector<pair<long long int, vector<int>>>(pow(2, numManobras), {-LLONG_MAX, {}}));

    pair<long long int, vector<int>> resultado = knapSack(0, 0, pista.secoes, manobras, manobrasPreCalc, MatrizDP);

    cout << resultado.first << endl;
    for(int i = 0; i < resultado.second.size(); i++) {
        int bitManobra = resultado.second[i];
        int num1 = __builtin_popcountll(bitManobra);
        cout << num1;
        for(int h = 0; h < numManobras; h++) {
            int bitAtualManobra = (bitManobra >> h) & 1;
            if(bitAtualManobra) {
                cout << " " << h + 1;
            }
        }
        cout << endl;
    }
}