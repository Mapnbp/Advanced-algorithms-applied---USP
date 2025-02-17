#include <iostream>
#include <vector>
#include <stack>

using namespace std;

typedef vector<int> vi;

void dfs(int u, const vector<vi>& graph, vi& visited, stack<int>& finishStack) {
    visited[u] = 1;
    for (int v : graph[u]) {
        if (!visited[v]) {
            dfs(v, graph, visited, finishStack);
        }
    }
    finishStack.push(u);  // Empilha ao terminar
}

void reverseDfs(int u, const vector<vi>& reverseGraph, vi& visited, vi& scc) {
    visited[u] = 1;
    scc.push_back(u);  // Coleta vértices do SCC atual
    for (int v : reverseGraph[u]) {
        if (!visited[v]) {
            reverseDfs(v, reverseGraph, visited, scc);
        }
    }
}

int main() {
    int n, m;

    do {
        cin >> n >> m;  

        if (n <= 0 || m <= 0) break;

        vector<vi> graph(n), reverseGraph(n);
        int u, v, r;

        // Leitura do grafo e construção do grafo reverso
        for (int i = 0; i < m; ++i) {
            cin >> u >> v;
            graph[u - 1].push_back(v - 1);
            reverseGraph[v - 1].push_back(u - 1);
            cin >> r;
            if (r == 2) {
                graph[v - 1].push_back(u - 1);
                reverseGraph[u - 1].push_back(v - 1);
            }
        }

        // Primeira passagem: ordem de término no grafo original
        vi visited(n, 0);
        stack<int> finishStack;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i, graph, visited, finishStack);
            }
        }

        // Segunda passagem: DFS no grafo invertido para identificar SCCs
        fill(visited.begin(), visited.end(), 0);  // Marca todos como não visitados
        int sccCount = 0;
        while (!finishStack.empty()) {
            int u = finishStack.top();
            finishStack.pop();
            if (!visited[u]) {
                vi scc;  // Armazena os vértices do SCC atual
                reverseDfs(u, reverseGraph, visited, scc);
                ++sccCount;
            }
        }

        // Verifica se o grafo é fortemente conexo
        cout << (sccCount == 1 ? 1 : 0) << endl;

    } while (n > 0 && m > 0);

    return 0;
}
