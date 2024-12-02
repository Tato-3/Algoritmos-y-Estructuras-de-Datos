#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
vector<int> stalls;

bool valeParaMid(int mid, int v){
    int ultima = stalls[0];
    v--;
    for(int i = 1; i < stalls.size(); i++){
        
        if(stalls[i]- ultima >= mid){
            v--;
            ultima = stalls[i];
            if(v == 0) return true;
        }
    }

    return false;
}

int posibleDif(int l, int h, int v){
    int res = 0;
    while(l <= h){
        int mid = (h+l) / 2;
        if(valeParaMid(mid, v)){
            res = mid;
            l = mid + 1;
        }else{
            h = mid - 1;
        }
    }
    return res;

}

int main(){
    int t;
    cin >> t;
    vector<int> res(t);
    for(int caso = 0; caso < t; caso++){
        int n;
        int c;
        cin >> n;
        cin >> c;
        stalls = vector<int>(n);
        for(int i = 0; i < n; i++){
            cin >> stalls[i];
        }
        sort(begin(stalls), end(stalls));
        
        int dif = posibleDif(1, stalls[n-1] - stalls[0], c);

        res[caso] = dif;
        
    }

    for(int i = 0; i < t; i++){
        cout << res[i] << endl;
    }
}