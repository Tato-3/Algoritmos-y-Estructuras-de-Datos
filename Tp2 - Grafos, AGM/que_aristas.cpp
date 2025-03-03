#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
int n;
vector<vector<int>> ady;
vector<string> respuestas;

struct Arista {
    int u, v, peso, indice;
};


class DSU {
    vector<int> rank, parent;
public:
    DSU(int n) {
        rank.resize(n, 0);
        parent.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }
 
    int find(int node){
 
        // En caso que nodo sea el representante
        if (node == parent[node]) return node;
 
        // Hago path compression
        return parent[node] = find(parent[node]);
    }
 
    void unionByRank(int u, int v) {
        int uRepresentative = find(u);
        int vRepresentative = find(v);
 
        // Si tienen el mismo representante, entonces pertenece al
        // mismo conjunto
        if (uRepresentative == vRepresentative) return;
 
        // Actualizamos el representante segun el caso del rank
        if (rank[uRepresentative] < rank[vRepresentative]) {
            parent[uRepresentative] = vRepresentative;
        } else if(rank[uRepresentative] > rank[vRepresentative]) {
            parent[vRepresentative] = uRepresentative;
        } else {
            parent[uRepresentative] = vRepresentative;
            rank[vRepresentative]++;
        }
    }

};

int caso_atleastone(vector<Arista>&E, int indice, int n) {
        DSU ds2(n);
        int pesoMST = 0;


        if (ds2.find(E[indice].u) != ds2.find(E[indice].v)) {
            pesoMST += E[indice].peso;
            ds2.unionByRank(E[indice].u, E[indice].v);
        }

        for (int i = 0; i < E.size(); i++) {

            if (ds2.find(E[i].u) != ds2.find(E[i].v)) {
                pesoMST += E[i].peso;
                ds2.unionByRank(E[i].u, E[i].v);
            }
        }

        for(int i=0; i < n; i++){
            if(ds2.find(i)!=ds2.find(0)){
                return INT_MAX;
            }
        }
        return pesoMST;
    }

int caso_any(const vector<Arista>&E, int indice, int n) {
        DSU ds1(n);
        int pesoMST = 0;
        
        for (int i = 0; i < E.size(); i++) {
            if (i == indice) {
                continue;
            }

            if (ds1.find(E[i].u) != ds1.find(E[i].v)) {
                pesoMST += E[i].peso;
                ds1.unionByRank(E[i].u, E[i].v);
            }
        }
        for(int i=0; i<n; i++){
            if(ds1.find(i)!=ds1.find(0)){
                return INT_MAX;
            }
        }
        return pesoMST;
    }

void kruskal(vector<Arista>& E, int n) {
    sort(E.begin(), E.end(), [](const Arista& a, const Arista& b) {
        return a.peso < b.peso;
    });

    DSU dsu(n);

    //Calculo el peso del MST, la idea es que si saco la arista y el peso del MST aumenta es porque era any, si es igual es at least one, y si no cambia es porque es none
    
    int peso_mst = 0;
    for(auto arista : E){
        if(dsu.find(arista.u) != dsu.find(arista.v)){
            peso_mst += arista.peso;
            dsu.unionByRank(arista.u, arista.v);
        }
    }

    for(int i = 0; i < E.size(); i++){
        int es_any = caso_any(E, i, n);
        int es_atleastone = caso_atleastone(E, i, n);

        if(es_any > peso_mst){
            respuestas[E[i].indice] = "any";
        }else if( es_atleastone == peso_mst){
            respuestas[E[i].indice] = "at least one";
        }
    }


}

int main() {
    int m;
    cin >> n >> m;
    vector<Arista> lista_aristas(m);
    respuestas.assign(m, "none");

    for (int i = 0; i < m; i++) {
        int nodo1, nodo2, peso_arista;
        cin >> nodo1 >> nodo2 >> peso_arista;
        lista_aristas[i] = {nodo1-1, nodo2-1, peso_arista, i};
    }
    
    kruskal(lista_aristas, n);
    
    for(auto res : respuestas){
        cout << res << endl;
    }



    return 0;
}

