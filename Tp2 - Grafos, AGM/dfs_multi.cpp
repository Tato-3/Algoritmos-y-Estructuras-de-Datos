#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <unordered_set>

using namespace std;


void IS_BRIDGE(int v,int to); // some function to process the found bridge
int n; // number of nodes
vector<vector<int>> adj; // adjacency list of graph
vector<tuple<int,int>> puentes;
vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    bool parent_skipped = false;
    for (int to : adj[v]) {
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
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}


int main(){
n = 4;
adj = {{}, {2}, {1,3}, {2}};
find_bridges();
for(int i = 0; i < puentes.size(); i++){
        cout << get<0>(puentes[i]) << " - " << get<1>(puentes[i]) << endl;
    }
return 0;
}