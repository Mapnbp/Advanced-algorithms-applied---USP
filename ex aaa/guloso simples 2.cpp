#include <bits/stdc++.h> 
using namespace std;

int main () {
    int n, aux; //tamanho do vetor, auxiliar
    int rodadas = 1; //quantas vezes eh preciso percorrer o vetor
    cin >> n;
    vector<int> indices(n + 1); // vetor onde colocamos o indice do vetor como a casa dele (ou seja, a ordem de leitura)

    for(int i = 0; i < n; i++) {
        cin >> aux;  // lendo os indices do vetor
        indices[aux] = i;
    }

    for(int i = 1; i < n; i++) {
        if(indices[i] > indices[i+1]) {
            rodadas++;  // toda vez que uam sequencia crescente eh quebrada contabilizamos mais uma rodada
        }
    }

    cout << rodadas << endl;
}