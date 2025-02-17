#include <bits/stdc++.h>
using namespace std;

// Função para verificar se um caractere é uma vogal
bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

// Função para calcular o custo de trocar duas letras
int swapCost(char a, char b) {
    if (a == b) return 0;
    if ((isVowel(a) && isVowel(b)) || (!isVowel(a) && !isVowel(b))) return 1;
    return 3;
}

// Função recursiva para construir as operações
void buildOperations(vector<vector<int>>& dp, const string& s1, const string& s2, int i, int j, string& operations) {
    if (i == 0 && j == 0) return; // Caso base

    if (i > 0 && dp[i][j] == dp[i - 1][j] + 2) { // Remoção
        buildOperations(dp, s1, s2, i - 1, j, operations);
        operations += "R:" + string(1, s1[i - 1]); // Adiciona a operação
    } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 2) { // Inserção
        buildOperations(dp, s1, s2, i, j - 1, operations);
        operations += "I:" + string(1, s2[j - 1]); // Adiciona a operação
    } else if (i > 0 && j > 0) { // Troca
        int cost = swapCost(s1[i - 1], s2[j - 1]);
        if (cost > 0) { // Só adiciona se houver custo
            buildOperations(dp, s1, s2, i - 1, j - 1, operations);
            operations += "T:" + string(1, s1[i - 1]) + "-" + string(1, s2[j - 1]); // Adiciona a operação
        } else {
            buildOperations(dp, s1, s2, i - 1, j - 1, operations); // Apenas avança
        }
    }
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size();
    int m = s2.size();

    // Matriz para armazenar os custos
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Inicialização da primeira linha e coluna
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = i * 2;
    }
    for (int j = 1; j <= m; ++j) {
        dp[0][j] = j * 2;
    }

    // Preenchimento da matriz DP
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int cost = swapCost(s1[i - 1], s2[j - 1]);
            dp[i][j] = dp[i - 1][j - 1] + cost;

            // Cálculo para remoção
            if (dp[i - 1][j] + 2 < dp[i][j]) {
                dp[i][j] = dp[i - 1][j] + 2;
            }

            // Cálculo para inserção
            if (dp[i][j - 1] + 2 < dp[i][j]) {
                dp[i][j] = dp[i][j - 1] + 2;
            }
        }
    }

    // Resultado
    int cost = dp[n][m];
    string operations;

    buildOperations(dp, s1, s2, n, m, operations); // Construção das operações

    cout << cost << endl;
    if (cost == 0) {
        cout << "nada a fazer" << endl;
    } else {
        cout << operations; // Imprime operações em uma única linha e sem espaços
    }

    return 0;
}
