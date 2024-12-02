#include<vector>
#include<iostream>
#include<tuple>

using namespace std;

const int INF = 99999999;

tuple<int, int> minTuple(const tuple<int, int> a, const tuple<int, int> b);

tuple<int,int> cc(vector<int> billetes, int n, int c, vector<vector<tuple<int,int>>>& memo){
    if(c <= 0) return {0, 0};
    if(n < 0 && c > 0) return {INF, INF};
    if(get<0>(memo[n][c]) != -1) return memo[n][c];
    
    memo[n][c] =  minTuple(cc(billetes, n-1, c, memo), make_tuple(get<0>(cc(billetes, n-1, c-billetes[n], memo)) + billetes[n], get<1>(cc(billetes, n-1, c-billetes[n], memo)) + 1));

    return memo[n][c];
}

tuple<int, int> cc_BottomUp(vector<int> billetes, int n, int c) {
    vector<vector<tuple<int, int>>> dp(n + 1, vector<tuple<int, int>>(c + 1, {INF, INF}));

    // Inicializar la tabla para el caso base
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = {0, 0}; // Si c es 0, el costo es 0 y el número de billetes es 0
    }

    // Llenar la tabla iterativamente
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= c; ++j) {
            dp[i][j] = dp[i - 1][j]; // No usar el billete i-ésimo
            if (j >= billetes[i - 1]) {
                dp[i][j] = minTuple(dp[i][j], make_tuple(get<0>(dp[i - 1][j - billetes[i - 1]]) + billetes[i - 1], get<1>(dp[i - 1][j - billetes[i - 1]]) + 1));
            }
        }
    }

    return dp[n][c];
}


tuple<int, int> minTuple(const tuple<int, int> a, const tuple<int, int> b) {
    if (get<0>(a) < get<0>(b)) return a;
    if (get<0>(a) > get<0>(b)) return b;
    if (get<1>(a) < get<1>(b)) return a;
    return b;
}

int main(){
    int n;
    cin >> n;

    int c;
    cin >> c;
    vector<int> billetes(n);
    for(int i = 0; i < n; i++){
        cin >> billetes[i];
    }

    tuple<int,int> res;

    vector<vector<tuple<int,int>>> memo(n+1, vector<tuple<int,int>>(c+1, {-1,-1}));

    res = cc(billetes, n-1, c, memo);

    cout << get<0>(res) << " " << get<1>(res) << endl;

    res = cc_BottomUp(billetes, 0, c);

    cout << get<0>(res) << " " << get<1>(res) << endl;

}