#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

vector<tuple<int, int>> m(vector<tuple<int, int>> mochila, int k) {
    if( k < 1){
        return {};
    }
    else{
        int i = 0; // declare and initialize 'i'
        return max(beneficio(m(mochila, k-get<0>(mochila[i]))), beneficio(m(mochila, k)));
    }
}

int beneficio(vector<tuple<int, int>> mochila){
    int res = 0;
    if(mochila.size() == 0){
        return 0;
    }else{
        for(int i = 0; i < mochila.size(); i++){
            res = get<1>(mochila[i]) + res;
        }
    }
    return res;
}

int main() {
    vector<tuple<int, int>> mochila;
    int k;
    int n;
    cin >> n; // Number of items
    for (int i = 0; i < n; ++i) {
        int weight, value;
        cin >> weight >> value;
        mochila.push_back(make_tuple(weight, value));
    }
    cin >> k;

    auto res = m(mochila, k);
    for (const auto& item : res) {
        cout << "(" << get<0>(item) << ", " << get<1>(item) << ") ";
    }
    cout << endl;

    return 0;
}