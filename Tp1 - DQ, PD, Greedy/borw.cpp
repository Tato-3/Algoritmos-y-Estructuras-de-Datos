#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<vector<int>>> memo;
vector<int> arr;
int INF = 1e7;

int borw(int i, int black, int white) {
    int n = arr.size();

    if (i == n) return 0;

    if (memo[i][black + 1][white + 1] != -1) return memo[i][black + 1][white + 1];

    int noAgrego = borw(i + 1, black, white);

    int pintoNegro = -INF;
    if (black == -1 || arr[black] < arr[i]) {
        pintoNegro = borw(i + 1, i, white) + 1;
    }

    int pintoBlanco = -INF;
    if (white == -1 || arr[i] < arr[white]) {
        pintoBlanco = borw(i + 1, black, i) + 1;
    }

    return memo[i][black + 1][white + 1] = max(noAgrego, max(pintoNegro, pintoBlanco));
}

int main() {
    vector<int> res;
    while (true) {
        int n;
        cin >> n;
        if (n == -1) break;

        arr = vector<int>(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        memo = vector<vector<vector<int>>>(
            n + 1, vector<vector<int>>(
                n + 1, vector<int>(n + 1, -1)
            )
        );

        int longi = borw(0, -1, -1);

        res.push_back(n - longi);
    }

    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << endl;
    }

    return 0;
}
