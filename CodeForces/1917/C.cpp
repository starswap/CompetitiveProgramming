#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N, D;
        cin >> N >> D;
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        vector<int> B(D);
        for (int i = 0; i < D; ++i) {
            cin >> B[i];
        }

        const int MAX_N = 8000;
        ll best = 0;
        for (int i = 0; i <= min(D - 1, 2 * MAX_N + 5); ++i) {
            ll pre_score = 0;
            for (int j = 0; j < N; ++j) {
                if (A[j] == j + 1) {pre_score++;}
            }
            // do i adds
            // then do one take
            // then do the rest as add/take alternating
            int remaining = D - i - 1;

            ll extra_score = (remaining/2);
            best = max(best, pre_score + extra_score);
            for (int j = 0; j < B[i]; ++j) {
                A[j]++;
            }
        }
        cout << best << endl;
    }
    return 0;
}