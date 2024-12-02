#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Función para verificar si un carácter es una consonante
bool esConsonante(char c) {
    c = tolower(c);
    return c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U' && isalpha(c);
}

bool tresConsonantesSeguidas(string palabra) {
    int contador = 0;

    for (int i = 0; i < palabra.length(); i++) {
        if (esConsonante(palabra[i])) {
            contador++;
            if (contador == 3) {
                return true;
            }
        } else {
            contador = 0;
        }
    }

    return false;
}

bool tresVocalesSeguidas(string palabra) {
    int contador = 0;

    for (int i = 0; i < palabra.length(); i++) {
        if (not(esConsonante(palabra[i]))) {
            contador++;
            if (contador == 3) {
                return true;
            }
        } else {
            contador = 0;
        }
    }

    return false;
}

string dobra(string word, string parcial, int i){
    
}

int main(){
    int n;
    string word;

    cin >> n;
    cin >> word;

    dobra(word, "", 0);
}