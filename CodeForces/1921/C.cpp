#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        ll N, F, A, B; cin >> N >> F >> A >> B;
        vector<ll> M(N + 1, 0);
        for (int n = 0; n < N; ++n) {
            cin >> M[n + 1];
        }
        ll total_charge = 0;
        for (int i = 0; i < N; ++i) {
            ll leave_on = (M[i + 1] - M[i]) * A;
            ll turn_off = B;
            total_charge += (ll) min(leave_on, turn_off);
        }
        // cout << total_charge << endl;
        if (total_charge < F) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        
    }
    return 0;
}