#include <bits/stdc++.h>
using namespace std;

int operacoesParaPrimo(int num) {
    int operacoes = 0;

    while (true) {
        bool ehPrimo = (num < 2) ? false : true;
        for (int i = 2; i * i <= num; i++) {
                ehPrimo = (num % i == 0) ? false : ehPrimo; 
                if (!ehPrimo) break;
        }
        if (ehPrimo) return operacoes;
        operacoes++;
        num++;
    }
}

int minimoOperacoes(const vector<vector<int>>& matrix, int n, int m) {
    int minOperacoes = INT_MAX;
    vector<int> operacoesLinha(n, 0);
    vector<int> operacoesColuna(m, 0);

    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) {
            int operacoes = operacoesParaPrimo(matrix[i][j]);
            operacoesLinha[i] += operacoes;
            operacoesColuna[j] += operacoes;
        }
    }
    for (int i = 0; i < max(n, m); i++) {
        minOperacoes = (i < n) ? min(minOperacoes, operacoesLinha[i]) : minOperacoes;
        minOperacoes = (i < m) ? min(minOperacoes, operacoesColuna[i]) : minOperacoes;
    }
    return minOperacoes;
}
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));

    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) {        
            cin >> matrix[i][j];
        }
    }
    cout << minimoOperacoes(matrix, n, m) << endl;

    return 0;
}
