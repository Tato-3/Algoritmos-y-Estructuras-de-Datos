#include<iostream>
#include<vector>

using namespace std;
int n;

int detBook(vector<int>& paginas){
    int res = 0;
    int paginaMax = 0;
    for(int i = 0; i < n; i++){
        
        paginaMax = max(paginaMax, paginas[i] - 1);

        if(i == paginaMax){
            res += 1;
        }
    }

    return res;
}

int main(){
    cin >> n;
    vector<int> paginas(n);
    for(int i = 0; i < n; i++){
        cin >> paginas[i];
    }

    cout << detBook(paginas) << endl;
}