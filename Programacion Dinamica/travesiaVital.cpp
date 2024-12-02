#include<iostream>
#include<vector>

using namespace std;

int minimo;
int m;
int n;
vector<vector<int>> matriz;
vector<vector<int>> memo;
const int INF = 999999999;

int travesiaVitalTD(int i, int j){

    if(i >= m || j >= n) return INF;

    if(i == m - 1 && j == n - 1){
        return max(1, 1 - matriz[i][j]);
    }

    if(memo[i][j] != -1) return memo[i][j];

    int der = travesiaVitalTD(i, j+1);
    int abj = travesiaVitalTD(i+1, j);

    memo[i][j] = max(1, min(der, abj) - matriz[i][j]);

    return memo[i][j];
}

void travesiaVitalBU(int k) {
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (m - 1 == i && n - 1 == j) {
                matriz[i][j] = max(1, 1 - matriz[i][j]);
            } else if (n - 1 == j) {
                matriz[i][j] = max(1, matriz[i + 1][j] - matriz[i][j]);
            } else if (m - 1 == i) {
                matriz[i][j] = max(1, matriz[i][j + 1] - matriz[i][j]);
            } else {
                matriz[i][j] = max(1, min(matriz[i + 1][j], matriz[i][j + 1]) - matriz[i][j]);
            }
        }
    }
}

int main(){
    cin >> m;
    cin >> n;
    int res;
    matriz = vector<vector<int>>(m, vector<int>(n));
    memo = vector<vector<int>>(m, vector<int>(n, -1));

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cin >> matriz[i][j];
        }
    }
    
    res = travesiaVitalTD(0, 0);
    travesiaVitalBU(0);

    cout << "Respuesta Top-Down: " << res << endl;
    cout << "Respuesta Bottom-Up: " << matriz[0][0] << endl;

    return 0;
}