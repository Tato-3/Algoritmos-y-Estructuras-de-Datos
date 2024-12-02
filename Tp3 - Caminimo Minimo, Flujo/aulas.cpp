#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

#define INF 101

using namespace std;

//USO FORD FULKERSON DE CP ALGORITHMS

int n;
int m;
vector<vector<int>> capacity;
vector<vector<int>> adj;
vector<vector<int>> respuestas;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

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
    vector<int> parent(n+2);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;

            respuestas[prev][cur] += new_flow;
            respuestas[cur][prev] -= new_flow;

            cur = prev;
        }
    }

    return flow;
}


int main(){
    cin >> n >> m;
    int sum_ai = 0;
    int sum_bi = 0;

    n = 2 * n;

    adj.assign(n+2, {});
    capacity.assign(n+2, vector<int>(n+2, 0));
    respuestas.assign(n+2, vector<int>(n+2, 0));

    for(int i = 1; i < n/2+1; i++){
        int c;
        cin >> c;
        adj[i].push_back(0);
        adj[0].push_back(i);
        capacity[0][i] = c;
        sum_ai += c;
    }

    for(int i = n/2+1; i < n+1; i++){
        int c;
        cin >> c;
        adj[n+1].push_back(i);
        adj[i].push_back(n+1);
        capacity[i][n+1] = c;
        sum_bi += c;
    }

    for(int i = 0; i < m; i++){
        int a; 
        int b;
        cin >> a >> b;

        adj[a].push_back(b+n/2);
        adj[b+n/2].push_back(a);
        
        adj[b].push_back(a+n/2);
        adj[a+n/2].push_back(b);
        
        capacity[a][b+n/2] = INF;
        capacity[b][a+n/2] = INF;
    
    }

    //Mismo vertice
    for(int i = 1; i <= n/2; i++){
        adj[i].push_back(n/2+i);
        adj[n/2+i].push_back(i);
        capacity[i][n/2+i] = INF;
    }

    int flujo = maxflow(0, n+1);

    if(flujo != sum_ai || flujo != sum_bi){
        cout << "NO" << endl;
    }else{
        cout << "YES" << endl;
        for(int i = 1; i < n/2+1; i++) {
            for(int j = n/2+1; j < n+1; j++) {
                cout << respuestas[i][j] << " ";
            }
        cout << endl;
        }
    }

    return 0;
}