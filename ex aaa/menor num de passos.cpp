#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> dist(n);

    for (int i = 0; i < n; ++i) {
        cin >> dist[i];
    }

    // BFS para encontrar o menor número de saltos
    queue<int> q;
    vector<int> steps(n, INT_MAX);
    q.push(0);
    steps[0] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Se chegamos ao final
        if (current == n - 1) {
            cout << steps[current] << endl;
            return 0;
        }

        // Verificar os próximos saltos
        for (int jump = 1; jump <= dist[current]; ++jump) {
            int next = current + jump;
            if (next < n && steps[next] == INT_MAX) { // Se ainda não visitado
                steps[next] = steps[current] + 1; // Atualiza os passos
                q.push(next); // Adiciona à fila
            }
        }
    }

    cout << "Salto impossivel" << endl; // Se não conseguir chegar ao final
    return 0;
}
