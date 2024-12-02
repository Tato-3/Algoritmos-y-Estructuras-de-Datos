#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

vector<int> res;
int maximo;
vector<int> candidatos;

void masS(vector<vector<int>> matriz, int k, vector<int> candidatos){
    int n = matriz.size();
    if(candidatos.size() == n){
        int candSum = accumulate(candidatos.begin(), candidatos.end(), 0);
        if(candSum == k){
            int temp = 0;
            for(int i = 0; i < matriz.size(); i++){
                for(int j = 0; j < matriz.size(); j++){
                    temp += candidatos[i] * candidatos[j] * matriz[i][j];
                }
            }
            if(temp > maximo){
                maximo = temp;
                res.clear();
                for (int i = 0; i < candidatos.size(); i++){
                    if(candidatos[i] == 1){
                        res.push_back(i+1);
                    }
                }
            }

            return;
        }else{
             return;
        }
    }
    else{
        candidatos.push_back(0);
        masS(matriz, k, candidatos);
        candidatos.pop_back();
        candidatos.push_back(1);
        masS(matriz, k, candidatos);
    }
}

int main(){
    int n;
    cin >> n;
    int k;
    cin >> k;

    vector<int> indices;
    for(int i = 0; i < n; i++){
        indices.push_back(i);
    }
    vector<vector<int>> matriz(n, vector<int>(n, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> matriz[i][j];
        }
    }

    masS(matriz, k, candidatos);

    for(int i = 0; i < res.size(); i++){
        cout << res[i] << endl;
    }
}