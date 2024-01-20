#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        vector<int> A(N);
        vector<int> B(M);
        for (int n = 0; n < N; ++n) {
            cin >> A[n];
        }
        for (int m = 0; m < M; ++m) {
            cin >> B[m];
        }

        sort(A.begin(), A.end());
        sort(B.begin(), B.end());

        vector<int> contrib(N);
        ll diff = 0;
        for (int i = 0; i < N; ++i) {
            contrib[i] = abs(A[i] - B[M - 1 - i]);
            diff += (ll) contrib[i];
        }

        ll best = diff;
        for (int i = N - 1, j = 0; i > -1; --i, ++j) {
            diff -= (ll) contrib[i];
            contrib[i] = abs(A[i] - B[j]);
            diff += (ll) contrib[i];
            best = max(best, diff);
        }

        cout << best << endl;

    }
    return 0;
}