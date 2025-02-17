#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> prices(n), pages(n);
    
    // Leitura dos preços e das páginas
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    // Declaração da matriz DP com (x + 1) colunas e preenchimento inicial com 0
    vector<int> dp(x + 1, 0);

    // Preenchimento da tabela DP
    for (int i = 0; i < n; i++) {
        // Varre o orçamento de trás para frente para evitar reutilizar o mesmo livro
        for (int j = x; j >= prices[i]; j--) {
            dp[j] = max(dp[j], dp[j - prices[i]] + pages[i]);
        }
    }

    // A resposta final é o valor máximo de páginas com o orçamento total x
    cout << dp[x] << endl;

    return 0;
}
