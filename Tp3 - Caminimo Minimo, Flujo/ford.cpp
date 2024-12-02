#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int n = 10; // Número de nodos (6 nodos bipartitos + fuente + sumidero)
vector<vector<int>> capacity(n, vector<int>(n, 0));
vector<vector<int>> adj(n);
vector<vector<int>> flow_passed(n, vector<int>(n, 0)); // Vector para almacenar el flujo pasado

void add_edge(int u, int v, int cap) {
    capacity[u][v] = cap;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = s;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            flow_passed[prev][cur] += new_flow; // Acumular el flujo pasado
            flow_passed[cur][prev] -= new_flow; // Ajustar el flujo en la dirección opuesta
            cur = prev;
        }
    }

    return flow;
}

int main() {
    int source = 0; // Nodo fuente
    int sink = 9;   // Nodo sumidero

    // Conjunto A: nodos 1, 2, 3, 4
    // Conjunto B: nodos 5, 6, 7, 8

    // Conectar fuente a nodos del conjunto A
    add_edge(source, 1, 1);
    add_edge(source, 2, 2);
    add_edge(source, 3, 6);
    add_edge(source, 4, 3);

    // Conectar nodos del conjunto A a nodos del conjunto B
    add_edge(1, 5, 101);
    add_edge(1, 6, 101);

    add_edge(2, 5, 101);
    add_edge(2, 6, 101);
    add_edge(2, 7, 101);
    add_edge(2, 8, 101);

    add_edge(3, 6, 101);
    add_edge(3, 7, 101);
    add_edge(3, 8, 101);

    add_edge(4, 6, 101);
    add_edge(4, 7, 101);
    add_edge(4, 8, 101);

    // Conectar nodos del conjunto B al sumidero
    add_edge(5, sink, 3);
    add_edge(6, sink, 5);
    add_edge(7, sink, 3);
    add_edge(8, sink, 1);

    cout << "El flujo máximo es " << maxflow(source, sink) << endl;

    for(int i = 1; i < n/2; i++) {
        for(int j = n/2; j < n-1; j++) {
            cout << flow_passed[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}