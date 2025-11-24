#include <bits/stdc++.h>


#define int long long
#define MULTITEST true

using namespace std;

void solve() {
    int N; cin >> N;
    vector<int> v(N);
    for (int n = 0; n < N; ++n) {
        cin >> v[n];
    }

    int prev = v[N - 2];
    int curr = v[N - 1];
    bool p1 = false;

    for (int i = 1; i < N; ++i) {
        if (v[i] <= v[i - 1]) {
            prev = v[i - 1] - v[i] + 1;
            curr = v[i - 1];
            p1 = true;
        }
    }

    int y = curr - prev + p1;
    int x = curr / (curr - prev);
    int r = max(x, y);

    cout << r << endl;

}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T = 1; if (MULTITEST) cin >> T;
    while(T--) {
        solve();
    }
}
