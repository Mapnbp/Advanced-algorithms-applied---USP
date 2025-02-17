#include <bits/stdc++.h>
using namespace std;

void encontra_raiz(vector<int>& vetor, int primo) {
    // Passa por todos os valores abaixo do número primo verificando o módulo da raiz de cada um
    for (long long int i = 0; i < primo; i++) {
        long long int resultado = (i * i) % primo;
        // Substituir apenas se for a primeira raiz a ter sido encontrada
        if (vetor[resultado] == -1) {
            vetor[resultado] = i;
        }
    }
}

int main() {
    int primo;
    cin >> primo;

    // Cria o vetor local e inicializa seus elementos
    vector<int> vetor(primo, -1);
    encontra_raiz(vetor, primo);

    // Exibe o vetor
    for (int i = 0; i < primo; i++) {
        cout << vetor[i] << " ";
    }
    cout << endl;

    return 0;
}
