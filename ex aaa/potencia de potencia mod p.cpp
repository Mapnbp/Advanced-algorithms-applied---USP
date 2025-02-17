#include <bits/stdc++.h>
using namespace std;

long long mod_exp(long long base, long long exp, long long p) {
    if (exp == 0) 
    return 1;
    long long metade = mod_exp(base, exp/2, p);
        metade = (metade * metade) % p;
    if (exp % 2 != 0) metade = (metade * base) % p;

    return metade;
}

int main() {
    const int p = 1e9 + 7;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        cout << mod_exp( a, mod_exp( b, c, p-1), p) << endl;
    }

    return 0;
}