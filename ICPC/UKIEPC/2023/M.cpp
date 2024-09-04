#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    int ans = 2 * a + (c >= 2 ? 2 * b + 3 : 0) + (max(c - 2, 0) / 2) * 3;
    cout << ans << endl;
}