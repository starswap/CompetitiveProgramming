#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int X, Y; cin >> X >> Y;
        bool can = false;
        if (X % 2 == 0) {
            int newX = X / 2;
            int newY = Y * 2;
            int newMin = min(newX, newY);
            int newMax = max(newX, newY);
            if (newMin != min(X, Y) || newMax != max(X, Y)) {
                can = true;
            }
        }
        if (Y % 2 == 0) {
            int newX = X * 2;
            int newY = Y / 2;
            int newMin = min(newX, newY);
            int newMax = max(newX, newY);
            if (newMin != min(X, Y) || newMax != max(X, Y)) {
                can = true;
            }
        }
        cout << ((can) ? "YES" : "NO") << endl;
    }
    return 0;
}