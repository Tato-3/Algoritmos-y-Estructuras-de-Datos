#include<iostream>
#include<vector>
#include<queue>
#include<utility>

using namespace std;

int n;
int m;

// Codigo de cp algorithms

const int INF = 1000000000;
vector<vector<pair<int, int>>> adj;

void dijkstra(int s, vector<int> & d, vector<int> & p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}



int main(){
    cin >> n;
    cin >> m;

    adj.resize(n);

    for(int i = 0; i < m; i++){
        int v, w, peso;
        cin >> v >> w >> peso;
        adj[v].push_back({w,peso});
        adj[w].push_back({v,peso}); 
    }

    vector<int> dist_s;
    vector<int> padres_s;
    vector<int> dist_t;
    vector<int> padres_t;

    dijkstra(0, dist_s, padres_s);

    dijkstra(n-1, dist_t, padres_t);

    
    int contador = 0;
    for(int i = 0; i < n; i++){
        for(auto arista: adj[i]){
            int v = arista.first;
            int peso = arista.second;
            if(dist_s[i] + peso + dist_t[v] == dist_s[n-1]) {
                contador += peso;
            }
        }
    }

    cout << contador * 2<< endl;

}
