#include <iostream>
#include <vector>

using namespace std;

vector<int> res;


void sumaK(vector<int> numeros, int k, int i){
    
    if (k == 0) {
        for (int num : res) {
            cout << num << " ";
        }
        cout << endl;
        return;  
    }

    if(i == numeros.size() || k < 0 ){
        return;
    }
    if(k > 0){
        sumaK(numeros, k, i+1);
        res.push_back(numeros[i]);
        sumaK(numeros, k-numeros[i], i+1);
        res.pop_back();
    }
}

int main(){
    int n;
    int k;
    cin >> n;
    cin >> k;

    vector<int> numeros(n, 0);

    for(int i = 0; i < n; i++){
        cin >> numeros[i];
    }

    sumaK(numeros, k, 0);

    return 0;

}