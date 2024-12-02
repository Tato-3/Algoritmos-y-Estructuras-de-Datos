#include <iostream>
#include <vector>

using namespace std;

bool esPrimo(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

int primeRing(vector<int> numeros, vector<int> parcial, int i){
    if(numeros.empty()){
        for(int j = 0; j < parcial.size()-1; j++){
            if(esPrimo(parcial[j] + parcial[j+1])){
                return 1 + primeRing(numeros, parcial, i-1);
            }else{
                return 0;
            }
        }
    }else{
        
    }

}


int main(){
    int n;
    cin >> n;

    vector<int> numeros(n, 0);

    for(int i = 0; i < n; i++){
        cin >> numeros[i];
    }

    int res = primeRing(numeros, {}, 0);

    cout << res << endl;
}