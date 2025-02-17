#include <bits/stdc++.h>
using namespace std;

// Função para construir o grafo
vector<pair<pair<int, int>, vector<pair<int, int>>>> construir_grafo(int linha, int coluna, set<pair<int, int>>& inacessiveis) {
    vector<pair<pair<int, int>, vector<pair<int, int>>>> grafo;

    for (int i = 0; i < linha; ++i) {
        for (int j = 0; j < coluna; ++j) {
            if (inacessiveis.find({i, j}) == inacessiveis.end()) {
                grafo.push_back({{i, j}, {}});
            }
        }
    }

    for (auto& vertice : grafo) {
        int x = vertice.first.first;
        int y = vertice.first.second;
        vector<pair<int, int>> vizinhos = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};

        for (auto& vizinho : vizinhos) {
            int vx = vizinho.first;
            int vy = vizinho.second;
            if (vx >= 0 && vx < linha && vy >= 0 && vy < coluna && inacessiveis.find({vx, vy}) == inacessiveis.end()) {
                vertice.second.push_back({vx, vy});
            }
        }
    }

    return grafo;
}

// Função para encontrar todos os caminhos usando BFS
void encontrar_caminhos_bfs(vector<pair<pair<int, int>, vector<pair<int, int>>>>& grafo, pair<int, int> inicio, pair<int, int> fim, vector<vector<pair<int, int>>>& todos_caminhos) {
    queue<pair<pair<int, int>, vector<pair<int, int>>>> fila;
    fila.push({inicio, {inicio}});

    while (!fila.empty()) {
        auto [nodo, caminho_atual] = fila.front();
        fila.pop();

        if (nodo == fim) {
            todos_caminhos.push_back(caminho_atual);
        } else {
            for (auto& vertice : grafo) {
                if (vertice.first == nodo) {
                    for (auto& vizinho : vertice.second) {
                        if (find(caminho_atual.begin(), caminho_atual.end(), vizinho) == caminho_atual.end()) {
                            auto novo_caminho = caminho_atual;
                            novo_caminho.push_back(vizinho);
                            fila.push({vizinho, novo_caminho});
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int M, N;
    cin >> M >> N;

    set<pair<int, int>> barreiras;
    vector<vector<int>> labirinto(M, vector<int>(N, 0));

    // Leitura dos obstáculos
    int x, y;
    while (cin >> x >> y) {
        barreiras.insert({x, y});
        labirinto[x][y] = 1; // Marca como obstáculo
    }

    auto grafo = construir_grafo(M, N, barreiras);

    pair<int, int> inicio = {0, 0};
    pair<int, int> fim = {M - 1, N - 1};

    vector<vector<pair<int, int>>> caminhos_possiveis;
    encontrar_caminhos_bfs(grafo, inicio, fim, caminhos_possiveis);

    // Contar e encontrar a menor distância
    int menor_caminho = INT_MAX;
    int contador = caminhos_possiveis.size();

    for (auto& caminho : caminhos_possiveis) {
        if (caminho.size() < menor_caminho) {
            menor_caminho = caminho.size();
        }
    }

    cout << contador << " " << (menor_caminho - 1) << endl;

    return 0;
} 