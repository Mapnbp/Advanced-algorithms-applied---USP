#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 25;

vector<int> graph[MAX_NODES];
bool visited[MAX_NODES];
bool edge_used[MAX_NODES][MAX_NODES];
int max_length;

void dfs(int node, int length) {
    max_length = max(max_length, length);

    for (int neighbor : graph[node]) {
        if (!edge_used[node][neighbor]) {
            // Marcar a aresta como usada
            edge_used[node][neighbor] = true;
            edge_used[neighbor][node] = true; // Para grafo não direcionado

            // Fazer a busca
            dfs(neighbor, length + 1);

            // Desmarcar a aresta
            edge_used[node][neighbor] = false;
            edge_used[neighbor][node] = false;
        }
    }
}

int main() {
    int n, m;
    while (cin >> n >> m, n || m) {
        // Limpar o grafo e as arestas visitadas
        for (int i = 0; i < n; i++) {
            graph[i].clear();
        }
        memset(edge_used, false, sizeof(edge_used));

        // Ler as arestas
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u); // Considerando que o grafo é não direcionado
        }

        max_length = 0;

        // Iniciar DFS a partir de cada nó
        for (int i = 0; i < n; i++) {
            memset(visited, false, sizeof(visited));
            dfs(i, 0);
        }

        cout << max_length << endl;
    }

    return 0;
}