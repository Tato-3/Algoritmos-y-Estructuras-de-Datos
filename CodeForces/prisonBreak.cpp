#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool canReachEnd(const string& s, int d) {
    int n = s.size();
    vector<bool> reachable(n + 2, false);
    reachable[0] = true;

    for (int i = 0; i <= n; ++i) {
        if (!reachable[i]) continue;
        if (i < n && s[i] == 'R') {
            for (int j = i + 1; j <= min(n + 1, i + d); ++j) {
                reachable[j] = true;
            }
        } else if (i < n && s[i] == 'L') {
            for (int j = max(0, i - d); j < i; ++j) {
                reachable[j] = true;
            }
        }
    }

    return reachable[n + 1];
}

int findMinimumD(const string& s) {
    int low = 1, high = s.size() + 1;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (canReachEnd(s, mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

int main() {
    int t;
    cin >> t;
    vector<int> res(t); // Inicializar el vector con el tamaño correcto
    for (int i = 0; i < t; i++) { // Corregir el incremento de i en el bucle
        string s;
        cin >> s;
        res[i] = findMinimumD(s);
    }

    for (int i = 0; i < t; i++) {
        cout << res[i] << endl;
    }
    return 0;
}
