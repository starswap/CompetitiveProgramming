#include <bits/stdc++.h>
using namespace std;

using ld = long double;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N;
        ld P;
        cin >> N >> P;
        P /= 100;

        ld ans = (pow(P, 1.0 - 1.0 / N) - P) * 100;
        cout << setprecision(15) << fixed;
        cout << "Case #" << t << ": " << ans << endl; 
    }
    return 0;
}
