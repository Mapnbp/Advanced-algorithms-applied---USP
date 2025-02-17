#include <bits/stdc++.h>
using namespace std;

// Função que calcula a distância entre dois pontos
double distancia(const pair<int, int>& p1, const pair<int, int>& p2) {
    return hypot(p1.first - p2.first, p1.second - p2.second);
}

// Função para encontrar a menor distância em uma faixa
double menorDist(vector<pair<int, int>>& strip, double d) {
    double minDist = d;
    
    // Ordena os pontos da faixa pela coordenada y (second do par)
    sort(strip.begin(), strip.end(), [](const pair<int, int>& p1, const pair<int, int>& p2) {
        return p1.second < p2.second;
    });

    // Compara cada ponto da faixa com os próximos pontos
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].second - strip[i].second) < minDist; ++j) {
            minDist = min(minDist, distancia(strip[i], strip[j]));
        }
    }

    return minDist;
}

// Função auxiliar de divisão e conquista
double divConq(vector<pair<int, int>>& pointsSortedX, vector<pair<int, int>>& pointsSortedY, size_t n) {
    if (n <= 3) {
        double minDist = numeric_limits<double>::max();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                minDist = min(minDist, distancia(pointsSortedX[i], pointsSortedX[j]));
            }
        }
        return minDist;
    }

    size_t mid = n / 2;
    pair<int, int> midPoint = pointsSortedX[mid];

    vector<pair<int, int>> leftY, rightY;
    leftY.reserve(mid);
    rightY.reserve(n - mid);

    // Dividindo os pontos ordenados por y em duas metades
    for (const auto& p : pointsSortedY) {
        (p.first <= midPoint.first ? leftY : rightY).push_back(p);
    }

    // Criação explícita dos vetores da metade direita
    vector<pair<int, int>> rightX(pointsSortedX.begin() + mid, pointsSortedX.end());
    vector<pair<int, int>> leftX(pointsSortedX.begin(), pointsSortedX.begin() + mid);

    // Recursão nas duas metades
    double dl = divConq(leftX, leftY, mid);
    double dr = divConq(rightX, rightY, n - mid);


    double d = min(dl, dr);

    // Construir a faixa de pontos próximos à linha de divisão
    vector<pair<int, int>> strip;
    strip.reserve(n);
    for (const auto& p : pointsSortedY) {
        if (abs(p.first - midPoint.first) < d) {
            strip.push_back(p);
        }
    }

    return min(d, menorDist(strip, d));
}

int main() {
    int n; // Número de coordenadas
    cin >> n; // Leitura do número de coordenadas

    vector<pair<int, int>> pontos(n);
    for (int i = 0; i < n; i++) {
        cin >> pontos[i].first >> pontos[i].second;
    }

    // Ordena o vetor por x, caso x1 = x2, ordena por y
    sort(pontos.begin(), pontos.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first)
            return a.second < b.second;
        return a.first < b.first;
    });

    // Ordena o vetor por y
    vector<pair<int, int>> pontosSortedY = pontos;
    sort(pontosSortedY.begin(), pontosSortedY.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });

    // Chama a função de divisão e conquista
    double resultado = divConq(pontos, pontosSortedY, n);

    cout << fixed << setprecision(2) << resultado << endl;

    return 0;
}
