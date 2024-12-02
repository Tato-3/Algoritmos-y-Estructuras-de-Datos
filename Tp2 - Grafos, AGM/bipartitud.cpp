#include<iostream>
#include<vector>
#include<queue>

using namespace std;
long long n;
vector<vector<long long> > lista_de_ady;
vector<long long> colores;

//BFS copiado para pintar los vertices de un color, y sus vecinos diferentes
void bfs_pintar(){
    queue<long long> cola;
    for(long long v = 1; v < n+1; v++){
        if(colores[v] == -1){
            cola.push(v);
            colores[v] = 0;

            while (!cola.empty()){
                long long nodo = cola.front();
                cola.pop();

                for(long long vecino : lista_de_ady[nodo]){
                    if(colores[vecino] == -1){
                        colores[vecino] = 1 - colores[nodo];
                        cola.push(vecino);
                    }
                }
            }
            
        }
    }

}

int main(){
    cin >> n;
    lista_de_ady.assign(n+1, vector<long long>());
    colores.assign(n+1, -1);
    for(long long i = 0; i < n-1; i++){
        long long u, v;
        cin >> u >> v;
        lista_de_ady[u].push_back(v);
        lista_de_ady[v].push_back(u);
    }
    bfs_pintar();
    long long v1 = 0, v2 = 0;
    for (long long i = 1; i <= n; i++) {
        if (colores[i] == 0)
            v1++;
        else
            v2++;
    }
    long long res = (v1 * v2) - (n-1);
    
    cout << res << endl;

    return 0;
}