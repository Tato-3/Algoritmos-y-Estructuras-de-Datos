#include<iostream>
#include<vector>
#include<cmath>

using namespace std;
vector<vector<int>> memo;

bool op(vector<int>& v, int i, int ac, int w){
    if(i == v.size() - 1){
        return ac == w;
    }
        
    if(ac > w) return false;


    if(memo[i][ac] != -1) return memo[i][ac];

    //Caso sumo
    bool sumo = op(v, i+1, ac + v[i+1], w);

    //Caso multiplico
    bool multiplico = op(v, i+1, ac * v[i+1], w);

    //Caso potencio
    bool potencio = op(v, i+1, pow(ac, v[i+1]), w);

    memo[i][ac] =  sumo || multiplico || potencio;

    return memo[i][ac];
}

int main(){
    int n;
    bool res;
    int w;
    cin >> n;
    cin >> w;

    vector<int> v(n);
    memo = vector<vector<int>>(n+1, vector<int>(w, -1));
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }

    res = op(v, 0, v[0], w);

    if(res){
        cout << "Se puede llegar a " << w << endl;
    }else{
        cout << "No se puede llegar a " << w << endl;
    }

    return 0;
}