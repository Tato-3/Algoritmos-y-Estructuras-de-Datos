#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <unordered_set>

using namespace std;


class Disjointset {
public:
    vector<int> rank;
    vector<int> parent;
    vector<int> size;
    Disjointset(int n) {
        rank.resize(n, 0);
        size.resize(n, 1);
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int findparent(int u) {
        if (u == parent[u]) {
            return u;
        }
        return parent[u] = findparent(parent[u]);
    }
    void unionbyrank(int u, int v) {
        int ulp_u = findparent(u);
        int ulp_v = findparent(v);

        if (ulp_u == ulp_v) {
            return;
        }
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_u] > rank[ulp_v]) {
            parent[ulp_v] = ulp_u;
        } else if (rank[ulp_u] == rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
            rank[ulp_v]++;
        }
    }
    void unionbysize(int u, int v) {
        int ulp_u = findparent(u);
        int ulp_v = findparent(v);

        if (ulp_u == ulp_v) {
            return;
        }
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else if (size[ulp_u] > size[ulp_v]) {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        } else if (size[ulp_u] == size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
    }
};

class Solution {
public:
    int pseudo_criticaledges(vector<vector<int>> new_edges, int index, int n) {
        Disjointset ds2(n);
        int totalwt = 0;

        int wt = new_edges[index][0];
        int idx = new_edges[index][1];
        int u = new_edges[index][2];
        int v = new_edges[index][3];

        if (ds2.findparent(u) != ds2.findparent(v)) {
            totalwt += wt;
            ds2.unionbysize(u, v);
        }

        for (int i = 0; i < new_edges.size(); i++) {

            int wt = new_edges[i][0];
            int idx = new_edges[i][1];
            int u = new_edges[i][2];
            int v = new_edges[i][3];

            if (ds2.findparent(u) != ds2.findparent(v)) {
                totalwt += wt;
                ds2.unionbysize(u, v);
            }
        }
        for(int i=0; i<n; i++){
            if(ds2.findparent(i)!=ds2.findparent(0)){
                return INT_MAX;
            }
        }
        return totalwt;
    }

    int criticaledges(vector<vector<int>> new_edges, int index, int n) {
        Disjointset ds1(n);
        int totalwt = 0;
        
        for (int i = 0; i < new_edges.size(); i++) {
            if (i == index) {
                continue;
            }

            int wt = new_edges[i][0];
            int idx = new_edges[i][1];
            int u = new_edges[i][2];
            int v = new_edges[i][3];

            if (ds1.findparent(u) != ds1.findparent(v)) {
                totalwt += wt;
                ds1.unionbysize(u, v);
            }
        }
        for(int i=0; i<n; i++){
            if(ds1.findparent(i)!=ds1.findparent(0)){
                return INT_MAX;
            }
        }
        return totalwt;
    }
    vector<vector<int>>findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<vector<int>> ans;
        vector<int> critical;
        vector<int> pseudo_critical;

        vector<vector<int>> new_edges;

        for (int i = 0; i < edges.size(); i++) {
            vector<int> temp;
            int u = edges[i][0];
            int v = edges[i][1];
            int wt = edges[i][2];
            int idx = i;

            temp = {wt, i, u, v};

            new_edges.push_back(temp);
        }
        int totalwt = 0;
        sort(new_edges.begin(), new_edges.end());
        Disjointset ds(n);
        for (auto it : new_edges) {
            int wt = it[0];
            int idx = it[1];
            int u = it[2];
            int v = it[3];

            if (ds.findparent(u) != ds.findparent(v)) {
                totalwt += wt;
                ds.unionbysize(u, v);
            }
        }
        for (int i = 0; i < new_edges.size(); i++) {
            int wt = criticaledges(new_edges, i, n);
            int wt1 = pseudo_criticaledges(new_edges, i, n);

            if (wt > totalwt) {
                critical.push_back(new_edges[i][1]);
            } else if (wt1 == totalwt) {
                pseudo_critical.push_back(new_edges[i][1]);
            }
        }
        ans.push_back(critical);
        ans.push_back(pseudo_critical);
        return ans;
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> aristas(m);
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        aristas[i] = {u-1, v-1, w};
    }

        Solution sol;
        vector<vector<int>> result = sol.findCriticalAndPseudoCriticalEdges(n, aristas);
    
        cout << "Critical edges: ";
        for (int edge : result[0]) {
            cout << edge << " ";
        }
        cout << endl;
    
        cout << "Pseudo-critical edges: ";
        for (int edge : result[1]) {
            cout << edge << " ";
        }
        cout << endl;
    
        return 0;

}