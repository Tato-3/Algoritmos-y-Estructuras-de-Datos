#include <iostream>
#include <vector>

using namespace std;

const int INF_NEG = -999999999;
vector<vector<int>> memo;

int astroTrade(vector<int>& p, int j, int c) {
    if (c > j || c < 0) return INF_NEG;
    if (j == p.size()) return 0;
    if (memo[j][c] == -1) {
        int nada = astroTrade(p, j + 1, c);
        int comprar = astroTrade(p, j + 1, c + 1) - p[j];
        int vender = astroTrade(p, j + 1, c - 1) + p[j];
        memo[j][c] = max(nada, max(comprar, vender));
    }
    return memo[j][c];
}

int main() {
    int n;
    cin >> n;
    vector<int> precios(n);
    for (int i = 0; i < n; i++) {
        cin >> precios[i];
    }
    int res;
    memo = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));

    res = astroTrade(precios, 0, 0);

    cout << "Resultado: " << res << endl;

    return 0;
}