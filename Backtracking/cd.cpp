#include <iostream>
#include <vector>
#include <chrono> // Incluye la biblioteca chrono para medir el tiempo

using namespace std;

const int NEG_INF = -1000000000;

int cd(vector<int> canciones, int capacidad, int i){

    if(i == canciones.size() && capacidad < 0){
        return NEG_INF;
    }
    if(i == canciones.size() && capacidad >= 0){
        return 0;
    }

    return std::max(cd(canciones, capacidad, i+1), canciones[i] + cd(canciones, capacidad-canciones[i], i+1));

}

int main(){
    int n;
    int capacidad;
    cin >> n;
    cin >> capacidad;
    vector<int> canciones;

    for(int i = 0; i < n; i++){
        int c;
        cin >> c;
        canciones.push_back(c);
    }

    auto start = chrono::high_resolution_clock::now();
    int res = cd(canciones, capacidad, 0);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;

    cout << res << endl;
    cout << "Tiempo de ejecución: " << duration.count() << " segundos" << endl;

}