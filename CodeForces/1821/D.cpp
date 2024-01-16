#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 2'000'000'005;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N, K; cin >> N >> K;
        vector<int> L(N);
        vector<int> R(N);
        for (int n = 0; n < N; ++n) {
            cin >> L[n];
        }
        for (int n = 0; n < N; ++n) {
            cin >> R[n];
        }

        int total = 0;
        int ones = 0;
        int best = INF;
        for (int e = 0; e < N; ++e) {
            if (R[e] - L[e] + 1 == 1) {
                ones++;
            }
            total += R[e] - L[e] + 1;
            if (total < K) continue;
            int spare = total - K; // min(total - K, R[e] - L[e] + 1);
            int r = e + 1;
            int skipped = min(spare, ones);
            int turning_cost = 2 * r - 2 * skipped;
            int cost = (R[e] - (spare - skipped)) + turning_cost;
            best = min(best, cost);
        }
        if (best == INF) {
            cout << -1 << endl;
        } else {
            cout << best << endl;
        }
    }
    return 0;
}
