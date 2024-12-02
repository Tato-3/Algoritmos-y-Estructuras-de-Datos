#include<iostream>
#include<vector>

using namespace std;
int n;
int m;

int parejasBaile(vector<int>& V, vector<int>& H){
    int i = 0;
    int j = 0;
    int res = 0;
    while (i < n && j < m){
        if(abs(V[i] - H[j]) == 1 || V[i] == H[j]){
            res += 1;
            j += 1;
            i += 1;
        }else if(V[i] > H[j]){
            j += 1;
        }else{
            i += 1;
        }
    }

    return res;
    
}


int main(){

    cin >> n >> m;
    vector<int> V(n);
    vector<int> H(m);
    for(int i = 0; i < n; i++){
        cin >> V[i];
    }
    for(int i = 0; i < m; i++){
        cin >> H[i];
    }

    cout << parejasBaile(V, H) << endl;
}