#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    
    vector<int> H(N);
    vector<int> R(N);
    vector<int> T(N);

    for (int n = 0; n < N; ++n) {
        cin >> H[n];
        cin >> R[n];
        cin >> T[n];
    }

    int maxH = 1825 * (*max_element(H.begin(), H.end()));
    int h;
    bool ok;

    for (h = 0; h < maxH; ++h) {
        ok = true;
        for (int n = 0; n < N; ++n) {
            int t = h % H[n];
            ok &= (t <= R[n] && R[n] <= T[n]) || (t >= T[n] && R[n] <= T[n]) || (T[n] <= t && t <= R[n]);
            if (!ok) break;
        }
        if (ok) {
            break;
        }
    }

    if (ok) {
        cout << h << endl;
    }
    else {
        cout << "impossible" << endl;
    }

    return 0;
}