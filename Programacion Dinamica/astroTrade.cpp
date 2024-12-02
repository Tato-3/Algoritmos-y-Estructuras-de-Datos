#include <iostream>
#include <vector>
#include <chrono> // Incluir la biblioteca chrono

using namespace std;

const int INF_NEG = -999999999;
vector<vector<int>> memo;

int astroTrade(vector<int>& p, int j, int c) {
    if (c > j || c < 0) return INF_NEG;
    if (j == 0) return 0;
    if (memo[j-1][c] == -1) {
        int vender = astroTrade(p, j - 1, c + 1) + p[j-1];
        int comprar = astroTrade(p, j - 1, c - 1) - p[j-1];
        int nada = astroTrade(p, j - 1, c);
        memo[j-1][c] = max(nada, max(comprar, vender));
    }
    return memo[j-1][c];
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

    auto start = chrono::high_resolution_clock::now(); // Capturar el tiempo de inicio
    res = astroTrade(precios, n, 0);
    auto end = chrono::high_resolution_clock::now(); // Capturar el tiempo de fin

    chrono::duration<double> duration = end - start; // Calcular la duración

    cout << "Resultado: " << res << endl;
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

    return 0;
}