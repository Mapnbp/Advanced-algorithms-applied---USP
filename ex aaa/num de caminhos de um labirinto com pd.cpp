#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX_N = 1000;
int dp[MAX_N][MAX_N];
char grid[MAX_N][MAX_N];

int main() {
    int n;
    cin >> n;

    // Leitura do grid
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    // Inicializando a posição de saída
    dp[0][0] = (grid[0][0] == '.' ? 1 : 0);

    // Preenchendo a primeira linha e a primeira coluna
    for (int i = 1; i < n; ++i) {
        if (grid[i][0] == '.') {
            dp[i][0] = dp[i-1][0];
        }
        if (grid[0][i] == '.') {
            dp[0][i] = dp[0][i-1];
        }
    }

    // Preenchendo o restante da matriz dp
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            if (grid[i][j] == '.') {
                dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD; // Cima e esquerda
                dp[i][j] = (dp[i][j] + dp[i-1][j-1]) % MOD; // Diagonal
            }
        }
    }

    // O resultado final é o valor na célula (n-1, n-1)
    cout << dp[n-1][n-1] << endl;

    return 0;
}
