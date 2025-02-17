#include <bits/stdc++.h>
using namespace std;

long long soluciona_PD(int n, vector<long long>& custo, vector<long long>& memo) {
    memo[n] = 0; // Não há custo adicional no último terno
    if (n > 1) {
        memo[n - 1] = abs(custo[n - 1] - custo[n]); // Custo ao mover do penúltimo para o último terno
    }

    // Percorre os ternos de trás para frente para calcular o menor custo
    for (int i = n - 2; i >= 1; i--) {
        // Considera as duas opções possíveis (ir para terno i+1 ou terno i+2)
        memo[i] = min(abs(custo[i] - custo[i + 1]) + memo[i + 1], abs(custo[i] - custo[i + 2]) + memo[i + 2]);
    }

    return memo[1]; // Retorna o menor custo começando do primeiro terno
}

int main() {
    int n; // número de ternos
    cin >> n;

    // Leitura dos custos Di de cada terno
    vector<long long> custo(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> custo[i];
    }

    // Vetor de memoização para armazenar os menores custos
    vector<long long> memo(n + 1, 0);

    // Calcula o menor custo de troca de ternos
    long long minCusto = soluciona_PD(n, custo, memo);
    
    // Imprime o menor custo possível
    cout << minCusto << endl;

    return 0;
}
