#include <iostream>
#include <vector>

using namespace std;

void cuadradoMagico(vector<vector<int>>& matriz, vector<bool>& usado, int i, int j, int m);
bool cuadradoMagicoValido(const vector<vector<int>>& matriz, int m);
int sumDiagonalPrincipal(const vector<vector<int>>& matriz);
int sumDiagonalSecundaria(const vector<vector<int>>& matriz);

int main(){
    int n;
    cin >> n;

    int m = n * (n * n + 1) / 2;  

    vector<vector<int>> matriz(n, vector<int>(n, 0));
    vector<bool> usado(n * n + 1, false);  

    cuadradoMagico(matriz, usado, 0, 0, m);

    return 0;
}

void cuadradoMagico(vector<vector<int>>& matriz, vector<bool>& usado, int i, int j, int m){
    int n = matriz.size();
    
    if(i == n){  
        if(cuadradoMagicoValido(matriz, m)){
            for (int k = 0; k < n; k++){
                for (int h = 0; h < n; h++){
                    cout << matriz[k][h] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        return;
    }

    int ni = (j == n - 1) ? i + 1 : i;
    int nj = (j + 1) % n;

    for(int num = 1; num <= n * n; num++){
        if(!usado[num]){
            matriz[i][j] = num;
            usado[num] = true;
            cuadradoMagico(matriz, usado, ni, nj, m);
            usado[num] = false;  
            matriz[i][j] = 0;    
        }
    }
}

bool cuadradoMagicoValido(const vector<vector<int>>& matriz, int m) {
    int n = matriz.size();
    
    for (int i = 0; i < n; i++) {
        int rowSum = 0, colSum = 0;
        for (int j = 0; j < n; j++) {
            rowSum += matriz[i][j];
            colSum += matriz[j][i];
        }
        if (rowSum != m || colSum != m) {
            return false;
        }
    }

    if (sumDiagonalPrincipal(matriz) != m || sumDiagonalSecundaria(matriz) != m) {
        return false;
    }

    return true;
}

int sumDiagonalPrincipal(const vector<vector<int>>& matriz) {
    int res = 0;
    for (int i = 0; i < matriz.size(); i++) {
        res += matriz[i][i];
    }
    return res;
}

int sumDiagonalSecundaria(const vector<vector<int>>& matriz) {
    int res = 0;
    int n = matriz.size();
    for (int i = 0; i < n; i++) {
        res += matriz[i][n - 1 - i];
    }
    return res;
}
