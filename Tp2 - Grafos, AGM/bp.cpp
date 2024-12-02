#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <unordered_set>

using namespace std;

int n;
vector<vector<int>> ady;
vector<tuple<int,int>> puentes;
vector<string> respuestas;

struct Arista {
    int u, v, peso, indice;
    string tipo;
};


class DSU {
    vector<int> rank, parent;
public:
    DSU(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for(int i = 0; i < n + 1; i++){
            parent[i] = i;
        }
    }
 
    int find(int node){
 
        // En caso que nodo sea el representante
        if (node == parent[node]) return node;
 
        // Hago path compression
        return parent[node] = find(parent[node]);
    }
 
    void unite(int u, int v) {
        int uRepresentative = find(u);
        int vRepresentative = find(v);
 
        // Si tienen el mismo representante, entonces pertenece al
        // mismo conjunto
        if (uRepresentative == vRepresentative) return;
 
        // Actualizamos el representante segun el caso del rank
        if (rank[uRepresentative] < rank[vRepresentative]) {
            parent[vRepresentative] = uRepresentative;
        } else if(rank[uRepresentative] > rank[vRepresentative]) {
            parent[uRepresentative] = vRepresentative;
        } else {
            parent[vRepresentative] = uRepresentative;
            rank[uRepresentative]++;
        }
    }
};

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    bool parent_skipped = false;
    for (int to : ady[v]) {
        if (to == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                puentes.push_back({v, to});
        }
    }
}

void find_bridges() {
    timer = 0;
    puentes.clear();
    visited.assign(n+1, false);
    tin.assign(n+1, -1);
    low.assign(n+1, -1);
    for (int i = 1; i < n + 1; ++i) {
        if (!visited[i])
            dfs(i);
    }
}

void kruskal(vector<Arista>& E, int n) {
    sort(E.begin(), E.end(), [](const Arista& a, const Arista& b) {
        return a.peso < b.peso;
    });

    DSU dsu(n);
    vector<tuple<int, int>> aristas_AGM;

    for (int i = 0; i < E.size(); i++) {
        auto& arista = E[i];
        if (i < E.size() - 1 && arista.peso == E[i + 1].peso) {
            int j = i;
            vector<tuple<int, int>> aristas_G;
            while (j < E.size() && arista.peso == E[j].peso) {
                aristas_G.push_back({E[j].u, E[j].v});
                j++;
            }
            ady.clear();
            ady.assign(n + 1, {});
            /*/ Agregar las aristas del AGM al grafo de adyacencia
            for (auto [u, v] : aristas_AGM) {
                int rep_u = dsu.find(u);
                int rep_v = dsu.find(v);
                ady[rep_u].push_back(rep_v);
                ady[rep_v].push_back(rep_u);
            }
            */
            // Agregar las aristas del mismo peso al grafo de adyacencia
            for (auto [u, v] : aristas_G) {
                int rep_u = dsu.find(u);
                int rep_v = dsu.find(v);
                ady[rep_u].push_back(rep_v);
                ady[rep_v].push_back(rep_u);
            }


            find_bridges();

            // Marcar las aristas según el resultado del DFS
            bool agregadas_al_AGM = false;
            for (int h = 0; h < aristas_G.size(); h++) {
                auto [u, v] = aristas_G[h];
                int rep_u = dsu.find(u);
                int rep_v = dsu.find(v);

                bool es_puente_rep = (find(puentes.begin(), puentes.end(), make_tuple(rep_u, rep_v)) != puentes.end()) ||
                                 (find(puentes.begin(), puentes.end(), make_tuple(rep_v, rep_u)) != puentes.end());

                bool es_puente_normal = (find(puentes.begin(), puentes.end(), make_tuple(u, v)) != puentes.end()) ||
                                 (find(puentes.begin(), puentes.end(), make_tuple(v, u)) != puentes.end());


                if (es_puente_rep || es_puente_normal) {
                    respuestas[E[i+h].indice] = "any"; 
                    dsu.unite(u, v);
                    aristas_AGM.push_back({u, v});
                } else {
                    respuestas[E[i + h].indice] = "at least one";
                    if (!agregadas_al_AGM) {
                        dsu.unite(u, v);
                        aristas_AGM.push_back({u, v});
                        agregadas_al_AGM = true;
                    }
                }
            }

            i = j - 1;

        } else if (dsu.find(arista.u) != dsu.find(arista.v)) {
            dsu.unite(arista.u, arista.v);
            respuestas[arista.indice] = "any";
            aristas_AGM.push_back({arista.u, arista.v});
        }
    }
}

int main() {
    int m;
    cin >> n >> m;
    n++;
    vector<Arista> lista_aristas(m);
    respuestas.assign(m, "none");

    for (int i = 0; i < m; i++) {
        int nodo1, nodo2, peso_arista;
        cin >> nodo1 >> nodo2 >> peso_arista;
        lista_aristas[i] = {nodo1, nodo2, peso_arista, i};
    }
    
    kruskal(lista_aristas, n);
    
    for(auto res : respuestas){
        cout << res << endl;
    }



    return 0;
}

