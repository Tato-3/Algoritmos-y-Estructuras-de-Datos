#include<iostream>
#include<vector>

using namespace std;

int potencia(int a, int b){
    if(b == 0) return 1;

    if(b % 2 == 0){
       int c = potencia(a, b/2);
       return c * c;
    }else{
        int c = potencia(a, (b-1)/2);
        return a * c * c;
    }
}


int main(){
    int a;
    cin >> a;
    int b;
    cin >> b;

    cout << potencia(a, b) << endl;
}