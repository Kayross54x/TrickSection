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

vector<Manobra> manobras;
vector<vector<long long int>> manobrasPreCalc;
vector<int> duracaoPreCalc;
vector<vector<pair<long long int, int>>> MatrizDP;
Pista pista;
int numSecoes, numManobras;
int potencia;

pair<long long int, int> knapSack(int currentSection, int manobraAtual) {
    if(currentSection >= pista.secoes.size()) return make_pair(0, 0);

    if(MatrizDP[currentSection][manobraAtual].first != -LLONG_MAX) {
        return MatrizDP[currentSection][manobraAtual];
    }

    long long int MaxPoints = 0;
    int manobrasUsadas;

    for(int proximaManobra = 0; proximaManobra < potencia; proximaManobra++) {
        int j = 0;
        int bitH = 0;
        long long int duracao = duracaoPreCalc[proximaManobra];

        if(duracao > pista.secoes[currentSection].tempoDeTravessia) {
            continue;
        }

        long long int pontosAcumulados = manobrasPreCalc[manobraAtual][proximaManobra] * pista.secoes[currentSection].bonificacao * __builtin_popcountll(proximaManobra);

        pair<long long int, int> result = knapSack(currentSection + 1, proximaManobra);

        if(pontosAcumulados + result.first > MaxPoints) {
            MaxPoints = pontosAcumulados + result.first;
            manobrasUsadas = proximaManobra;
        }
    }

    MatrizDP[currentSection][manobraAtual].first = MaxPoints;
    MatrizDP[currentSection][manobraAtual].second = manobrasUsadas;
    return MatrizDP[currentSection][manobraAtual];
}

int main() {
    scanf("%d %d", &numSecoes, &numManobras);

    potencia = pow(2, numManobras);

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

    manobrasPreCalc.resize(potencia, vector<long long int>(potencia));
    duracaoPreCalc.resize(potencia);

    for(int i = 0; i < potencia; i++) {
        int sum = 0;

        for(int j = 0; j < numManobras; j++) {
            int bitH = (i >> j) & 1;
            if(bitH == 1) {
                sum += manobras[j].duracao;
            }
        }
        duracaoPreCalc[i] = sum;
    }

    for(int i = 0; i < potencia; i++) {
        for(int j = 0; j < potencia; j++){
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

    MatrizDP.resize(numSecoes, vector<pair<long long int, int>>(potencia, {-LLONG_MAX, 0}));

    pair<long long int, int> resultado = knapSack(0, 0);

    cout << resultado.first << endl;
    int cur = 0;

    for(int j = 0; j < numSecoes; j++) {
        int aux = MatrizDP[j][cur].second;
        vector<int> auxVector;

        for(int x = 0; x < numManobras; x++) {
            if(aux & (1 << x)) {
                auxVector.push_back(x + 1);
            }
        }

        cout << auxVector.size() << " ";
        for(int i = 0; i < auxVector.size(); i++) {
            cout << auxVector[i] << " ";
        }
        cout << endl;

        cur = aux;
    }
}