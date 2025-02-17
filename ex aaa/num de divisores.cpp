#include <bits/stdc++.h>
using namespace std;

void precomputeDivisors(int maxValue, vector<int>& numDiv) {
    for (int i = 1; i <= maxValue; ++i) {
        for (int j = i; j <= maxValue; j += i) {
            numDiv[j]++;
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    
    int maxX = 0;
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
        maxX = max(maxX, numbers[i]);
    }
    
    vector<int> numDiv(maxX + 1, 0);
    precomputeDivisors(maxX, numDiv);
    
    for (int i = 0; i < n; ++i) {
        cout << numDiv[numbers[i]] << "\n";
    }

    return 0;
}
