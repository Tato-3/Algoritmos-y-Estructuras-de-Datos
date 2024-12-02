#include <iostream>
#include <vector>
#include <tuple>
#include<algorithm>
using namespace std;

int busyman(vector<tuple<int,int>>& actividades){
    int res = 1;
    //Ordeno de mayor a menor por el comienzo de la act
    sort(actividades.begin(), actividades.end(), [](tuple<int,int>& a, tuple<int,int>& b) {
        return get<0>(a) > get<0>(b);
    });
    int j = 0;
    for(int i = 1; i < actividades.size(); i++){
        int inicio = get<0>(actividades[j]);
        int final = get<1>(actividades[i]);
        if( inicio >= final){
            res += 1;
            j = i;
        }
    }
    
    return res;

}


int main(){
    int t;
    cin >> t;
    vector<int>res;

    for(int i = 0; i < t; i++){
        int n;
        cin >> n;
        vector<tuple<int,int>> actividades(n);
        for(int j = 0; j < n; j++){
            int s;
            int f;
            cin >> s;
            cin >> f;
            actividades[j] = make_tuple(s, f);
        }

        int resultado = busyman(actividades);
        res.push_back(resultado);
    }

    for(int i = 0; i < t; i++){
        cout << res[i] << endl;
    }

    return 0;
}