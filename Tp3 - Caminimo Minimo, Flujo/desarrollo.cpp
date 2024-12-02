#include<iostream>
#include<vector>

using namespace std;
long long n;
vector<vector<long long>> matriz;
vector<long long> orden;


int main(){
    cin >> n;
    matriz.assign(n, vector<long long>(n));
    orden.resize(n);
    vector<long long> respuestas(n);
    vector<bool> usados(n, false);

    for(long long i = 0; i < n; i++){
        for(long long j = 0; j < n; j++){
            cin >> matriz[i][j];
        }
    }

    for(long long i = 0; i < n; i++){
        cin >> orden[i];
        orden[i]--;
    }

    for(long long k = n-1; k >= 0; k--){
        long long res = 0;
        long long num = orden[k];
        usados[num] = true;
        for(long long i = 0; i < n; i++){
            for(long long j = 0; j < n; j++){
                matriz[i][j] = min(matriz[i][j], matriz[i][num] + matriz[num][j]);
                if(usados[i] && usados[j]) res += matriz[i][j];
            }
        }
        respuestas[k] = res;


    }
    
    for(long long i = 0; i < n; i++){
        cout << respuestas[i] << " ";
    }

    return 0;
}