#include <bits/stdc++.h> 
using namespace std;

int main () {
    int n, custoAtual = 0, custoMax = 0; // numero de tarefas
    cin >> n;
    vector<pair<int,int>> tarefa(n); // vetor que guarda o custo da tarefa e prazo

    for(int i = 0; i < n; i++) { // leitura do vetor
        cin >> tarefa[i].first >> tarefa[i].second;
    }

    // ordenando o vetor
    sort(tarefa.begin(), tarefa.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    });

    for(int i = 0; i < n; i++) { 
        custoAtual += tarefa[i].first; // somando o custo de cada tarefa individualmente
        custoMax +=  tarefa[i].second - custoAtual; // calculando o custo maximo
    }

    cout << custoMax << endl;

    return 0;
}
