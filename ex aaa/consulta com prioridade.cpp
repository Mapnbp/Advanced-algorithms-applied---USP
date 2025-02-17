#include <bits/stdc++.h> 
using namespace std;

struct Fila {
    int id;   // identificador da consulta
    int t;    // intervalo entre respostas
    int prox; // próximo tempo em que o elemento deve retornar

    // sobrecarga do operador de comparação para garantir que a consulta com menor tempo seja processada primeiro.
    // em caso de empate, a consulta com o menor ID deve ser processada.
    bool operator<(const Fila& other) const {
        if (prox == other.prox)
            return id > other.id;
        return prox > other.prox;
    }
};

int main () {

    int n, k; // n numero de elementos, k numero de consultas a serem realizadas
    cin >> n;

    priority_queue<Fila> pq;

    // leitura inicial
    for (int i = 0; i <n; i++) {
        int id, t; // definidos pelo exercicio
        string query; // como nao tem uso pratico, vamos ler e descartar

        cin >> query >> id >> t; // leitura
        pq.push({id, t, t}); // armazenamento
    }

    cin >> k;

    for(int i = 0; i < k; i++) {
        Fila atual = pq.top(); // auxiliar para o primeiro da fila
        pq.pop();

        cout << atual.id << endl; // exibindo o primeiro da fila
        atual.prox += atual.t; // atualiza o tempo do atual da fila
        pq.push(atual); // e envia ele para o "final" (ele encontra sua posição correta)

    }
    
    return 0;
}