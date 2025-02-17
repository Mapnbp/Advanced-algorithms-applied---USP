#include <bits/stdc++.h>
using namespace std;

// Função que resolve o TSP usando programação dinâmica com bitmask
int tsp(int pos, int mask, vector<vector<int>>& distancia, vector<vector<int>>& dp, int start) {
    // Caso base: se todas as cidades foram visitadas e estamos voltando à cidade inicial
    if (mask == (1 << distancia.size()) - 1) {
        return distancia[pos][start]; // Retorna a distância para a cidade inicial
    }

    // Se o valor já foi calculado, retorna-o
    if (dp[pos][mask] != -1) {
        return dp[pos][mask];
    }

    int ans = INT_MAX;

    // Itera sobre todas as cidades para encontrar a próxima cidade a visitar
    for (int city = 0; city < distancia.size(); ++city) {
        // Se a cidade ainda não foi visitada e não é a cidade atual
        if (!(mask & (1 << city)) && city != pos) {
            // Calcula o custo ao visitar essa cidade e a recursão subsequente
            int newCost = distancia[pos][city] + tsp(city, mask | (1 << city), distancia, dp, start);
            ans = min(ans, newCost);
        }
    }

    return dp[pos][mask] = ans;
}

int main() {
    int n, s;
    cin >> n >> s;

    vector<vector<int>> distancia(n, vector<int>(n)); // Matriz de distâncias
    // Preenchendo a matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> distancia[i][j];
        }
    }

    // Tabela de DP para armazenar os resultados intermediários
    vector<vector<int>> dp(n, vector<int>(1 << n, -1));

    // Calcula o menor custo para o passeio começando na cidade s
    int minCost = tsp(s, 1 << s, distancia, dp, s);

    cout << minCost << endl;

    return 0;
}
