#include <bits/stdc++.h>
using namespace std;

// Função que verifica se é possível alocar os livros de forma que
// nenhum estudante receba mais do que "mid" páginas
bool verifica(int mid, const vector<int>& livros, int m) {
    int estudantes = 1;
    int paginas_alocadas = 0;
    
    for (int paginas : livros) {
        if (paginas > mid) {
            return false; // Se uma única quantidade de páginas já excede o mid, não é possível
        }
        if (paginas_alocadas + paginas > mid) {
            estudantes++;
            paginas_alocadas = paginas;
            if (estudantes > m) {
                return false;
            }
        } else {
            paginas_alocadas += paginas;
        }
    }
    
    return true;
}

// Função principal que encontra a menor quantidade máxima de páginas
// que podem ser alocadas a um estudante
int aloca_livros(vector<int>& livros, int n, int m) {
    // Ordena o vetor de livros
    sort(livros.begin(), livros.end());

    if (m > n) {
        return *max_element(livros.begin(), livros.end());
    }
    
    int low = *max_element(livros.begin(), livros.end()); // O maior número de páginas de um livro
    int high = accumulate(livros.begin(), livros.end(), 0); // A soma de todas as páginas dos livros
    
    int resultado = high; // Valor inicial do resultado
    
    while (low <= high) {
        int mid = (low + high) / 2;
        
        if (verifica(mid, livros, m)) {
            resultado = mid; // Atualiza o resultado com o valor mínimo possível
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    return resultado;
}

int main() {
    // Leitura dos valores de entrada
    int n, m;
    cin >> n >> m;
    vector<int> livros(n);
    
    for (int i = 0; i < n; i++) {
        cin >> livros[i];
    }
    
    // Calcula e imprime o resultado
    cout << aloca_livros(livros, n, m) << endl;
    
    return 0;
}
