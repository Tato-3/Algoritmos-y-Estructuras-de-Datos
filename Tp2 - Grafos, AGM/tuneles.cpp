#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n;
vector<vector<int>> lista_de_ady;
vector<int> distancias;

void bfs_distancias(){
    queue<int> cola;
    cola.push(1);
    distancias[1] = 0;
    
    while (!cola.empty()){
        int nodo = cola.front();
        cola.pop();

        for (int vecino : lista_de_ady[nodo]) {
            if (distancias[vecino] == -1) {
                distancias[vecino] = distancias[nodo] + 1;
                cola.push(vecino);
            }
        }
    }
}


int main(){
    cin >> n;
    lista_de_ady.assign(n+1, vector<int>());
    distancias.assign(n+1, -1);

    for(int i = 1; i < n; i++){
        lista_de_ady[i].push_back(i+1);
        lista_de_ady[i+1].push_back(i);
    }

    int contador = 1;
    while(contador < n+1){
        int u;
        cin >> u;
        if(contador != u && abs(contador - u) != 1){
            lista_de_ady[contador].push_back(u);
        }
        contador++; 
    }

    bfs_distancias();

    for(int i = 1; i < n+1; i++){
        cout << distancias[i] << endl;
    }

    return 0;
}