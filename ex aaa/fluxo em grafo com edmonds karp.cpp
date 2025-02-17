#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <sstream>
#include <cstring>
using namespace std;

// Definições
const int MAX_NODES = 100; // Número máximo de nós no grafo
const int INF = 1e9;       // Valor "infinito"

// Grafo para fluxo
vector<int> adj[MAX_NODES];   // Lista de adjacências
int capacity[MAX_NODES][MAX_NODES]; // Capacidades
int parent[MAX_NODES];        // Array para armazenar o caminho

// BFS para encontrar o caminho com capacidade residual
bool bfs(int source, int sink) {
    memset(parent, -1, sizeof(parent));
    queue<pair<int, int>> q;
    q.push({source, INF});

    while (!q.empty()) {
        int current = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[current]) {
            if (parent[next] == -1 && capacity[current][next] > 0) {
                parent[next] = current;
                int new_flow = min(flow, capacity[current][next]);
                if (next == sink)
                    return true; // Encontrou um caminho até o sumidouro
                q.push({next, new_flow});
            }
        }
    }
    return false;
}

// Algoritmo de Edmonds-Karp para fluxo máximo
int edmondsKarp(int source, int sink) {
    int flow = 0;

    while (bfs(source, sink)) {
        int current = sink;
        int path_flow = INF;

        // Determinar o fluxo mínimo no caminho encontrado
        while (current != source) {
            int prev = parent[current];
            path_flow = min(path_flow, capacity[prev][current]);
            current = prev;
        }

        // Atualizar as capacidades residuais
        current = sink;
        while (current != source) {
            int prev = parent[current];
            capacity[prev][current] -= path_flow;
            capacity[current][prev] += path_flow;
            current = prev;
        }

        flow += path_flow;
    }
    return flow;
}

// Função para processar a entrada e construir o grafo
bool processDay(vector<string>& jobs) {
    int source = 0;
    int sink = MAX_NODES - 1;
    int totalDemand = 0;

    // Limpar o grafo
    for (int i = 0; i < MAX_NODES; ++i) {
        adj[i].clear();
        for (int j = 0; j < MAX_NODES; ++j) {
            capacity[i][j] = 0;
        }
    }

    // Adicionar tarefas e processadores ao grafo
    for (const string& job : jobs) {
        stringstream ss(job);
        char task;
        int users;
        string processors;

        // Parse da linha: tarefa, usuários e processadores
        ss >> task >> users >> processors;
        int taskNode = task - 'A' + 1; // Nós das tarefas: 1-26
        totalDemand += users;

        // Fonte -> Tarefa
        adj[source].push_back(taskNode);
        adj[taskNode].push_back(source);
        capacity[source][taskNode] = users;

        // Tarefa -> Processadores
        for (char p : processors) {
            int processorNode = 27 + (p - '0'); // Nós dos processadores: 27-36
            adj[taskNode].push_back(processorNode);
            adj[processorNode].push_back(taskNode);
            capacity[taskNode][processorNode] = 1;

            // Processadores -> Sumidouro
            adj[processorNode].push_back(sink);
            adj[sink].push_back(processorNode);
            capacity[processorNode][sink] = 1;
        }
    }

    // Verificar se o fluxo máximo atende à demanda total
    return edmondsKarp(source, sink) == totalDemand;
}

int main() {
    string line;
    vector<string> jobs;
    bool isFirst = true;

    while (getline(cin, line)) {
        if (line.empty()) {
            if (!jobs.empty()) {
                if (!isFirst) cout << "\n";
                isFirst = false;
                cout << (processDay(jobs) ? "YES" : "NO");
                jobs.clear();
            }
        } else {
            // Processar cada entrada corretamente, removendo ";"
            line = line.substr(0, line.find(';'));
            jobs.push_back(line);
        }
    }

    // Processar o último conjunto de jobs
    if (!jobs.empty()) {
        if (!isFirst) cout << "\n";
        cout << (processDay(jobs) ? "YES" : "NO");
    }

    return 0;
}
