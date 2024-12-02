#include<iostream>
#include<vector>

using namespace std;

int n;
const int INF_NEG = -9999999;
vector<int> peso;
vector<int> soportes;
vector<bool> enPila;
vector<int> memo;

int pilaC(int i){

    //No hay mas cajas por agregar
    if(i < 0) return 0;

    //Caso base para saber si el soporte de la caja aguanta todos los pesos de las cajas en la pila
    if(i == 0){
        if(soportes[0] > 0 && peso[0] <= soportes[0]) return 1;
        else return 0;
    }

    //Me fijo si ya lo calcule entonces lo devuelvo
    if(memo[i] != -1) return memo[i];

    int noAgrego = pilaC(i-1);
    int agrego = INF_NEG;
    
    // Si el soporte de i es menor que cero no me interesa y ademas no tiene que estar en la pila
    if(soportes[i] > 0 && !enPila[i]){

        enPila[i] = true;

        //Resto el peso de la caja i a todos las cajas agregadas en la pila
        for(int j = 0; j < n; j++){
            if(enPila[j]) soportes[j] -= peso[i];
        }

        bool loAgrego = true;

        //Compruebo que las cajas agregadas cumplen con el soporte para su pesos
        for(int j = 0; j < n; j++){
            if(enPila[j] && soportes[j] < 0){
                loAgrego = false;
                break;
            }
        }

        if(loAgrego) agrego = pilaC(i-1) + 1;

        //Restauro los soportes
        for(int j = 0; j < n; j++){
            if(enPila[j]) soportes[j] += peso[i];
        }

        //Restauro que no este en la Pila
        enPila[i] = false;

    }
    
    //Me lo guardo en la memo por si lo necesito despues
    memo[i] =  max(noAgrego, agrego);

    return memo[i];

}

int main(){
    cin >> n;

    peso = vector<int>(n);
    soportes = vector<int>(n);
    enPila = vector<bool>(n, false);
    memo = vector<int>(n+1, -1);

    for(int i = 0; i < n; i++){
        cin >> peso[i];
        cin >> soportes[i];
    }
    int res;

    res = pilaC(n-1);

    cout << res << endl;

}

