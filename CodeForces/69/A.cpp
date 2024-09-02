#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    int a, b, c;
    a = 0; b = 0; c = 0;
    for (int i = 0; i < N; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        a += x;
        b += y;
        c += z;
    }
    // cout << a << b << c << endl;
    if ((a == 0) && (b == 0) && (c == 0)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}