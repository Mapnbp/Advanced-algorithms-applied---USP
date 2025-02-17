#include <bits/stdc++.h> 
using namespace std;

int main() {

    int t; // t é o número de casos de teste
    cin >> t;
    vector<int> casos(t);

    for(int i = 0; i < t; i++) {
        int n; // n assuntos do cdf
        string tema;
        cin >> n;

        unordered_map<string, int> assuntos; // unordered_map que armazena o nome e o tempo

        for (int j = 0; j < n; j++) {
            string nome; // auxiliar da string
            int dias; // auxiliar do tempo

            cin >> nome >> dias;
            // armazena no unordered_map com o nome como chave e dias como valor
            assuntos[nome] = dias;
        }
        
        int d; // prazo
        cin >> d >> tema;
        auto it = assuntos.find(tema); // busca o tema do trabalho
        if (it != assuntos.end()) {
            if(it->second <= d) {
                casos[i] = 1; // 1 sinaliza que o trabalho é feito no prazo
            }
            else if(it->second <= d+5) {
                casos[i] = 0; // 0 sinaliza que o trabalho será entregue com atraso
            }
            else {
                casos[i] = 2; // 2 sinaliza que não é possível fazer o trabalho
            }
        }
        else {
            casos[i] = 2;
        }
    }

    for(int i = 0; i < t; i++) { // auto explicativo
        switch (casos[i]){
            case 0:
                cout << "Case " << i+1 << ": Atrasado" << endl;
                break;
            case 1:
                cout << "Case " << i+1 << ": Ufa!" << endl;
                break;
            case 2:
                cout << "Case " << i+1 << ": Deu ruim! Va trabalhar" << endl;
                break;
        }
    }

    return 0;
}

//big o ( t n )