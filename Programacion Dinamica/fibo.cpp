#include<iostream>
#include<vector>

using namespace std;

int fiboTopDown(int n, vector<int>& memo){
    if(n <= 2) return 1;

    if(memo[n] != -1) return memo[n];

    memo[n] = fiboTopDown(n-1, memo) + fiboTopDown(n-2, memo);

    return memo[n];
}

int fiboBottomUp(int n){
    if(n <= 2) return 1;
    vector<int> memo(n+1, -1);
    memo[0] = memo[1] = memo[2] = 1;
    for(int i = 3; i < n + 1; i++){
        memo[i] = memo[i-1] + memo[i-2];
    }
    return memo[n];
}

int main(){
    int n;
    cin >> n;
    vector<int> memo(n+1, -1);
    int resTD;
    int resBU;
    resTD = fiboTopDown(n, memo);
    resBU = fiboBottomUp(n);
    cout << "Top-Down: " << resTD << endl;
    cout << "Bottom-Up: " << resBU << endl;

    return 0;
}