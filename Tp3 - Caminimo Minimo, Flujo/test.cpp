#include <iostream>
#include<vector>

using namespace std;

int main(){
    vector<vector<int>> matriz = {
        {0,0,0,0,0},
        {0,1,0,0,0},
        {0,2,0,0,0},
        {0,0,5,1,0},
        {0,0,0,2,1}
    };

    for(int i = 1; i < 5; i++){
        for(int j = 1; j < 5; j++){
            if(matriz[i][j] != 0){
                cout << "Del aula " << i << " deben moverse: " << matriz[i][j] << " al aula " << j << endl;
            }
        }
    }
}