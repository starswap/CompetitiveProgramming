#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        int b = N % 11;
        int a = (N - 111 * b) / 11;
        if (a >= 0 && b >= 0 && N == 11 * a + 111 * b) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
