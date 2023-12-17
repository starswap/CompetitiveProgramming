#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<int> A(N);
        for (int n = 0; n < N; ++n) {
            cin >> A[n];
        }

        map<int, int> seen;
        vector<int> before(N, -1);
        vector<int> after(N, -1);

        for (int i = 0; i < N; ++i) {
            auto bigger = seen.upper_bound(i + 1);
            if (bigger == seen.end()) {
                // Nothing bigger comes before
            } else if (next(bigger) == seen.end()) {
                // One thing bigger comes before
                before[i] = (*bigger).second;
            } else {
                // More than one thing bigger comes before, so impossible to swap around
                before[i] = -2;
            }
            seen.emplace(A[i], i);
        }

        seen.clear();

        for (int i = N - 1; i >= 0; --i) {
            auto smaller = seen.upper_bound(-(i + 1));
            if (smaller == seen.end()) {
                // Nothing smaller comes after
            } else if (next(smaller) == seen.end()) {
                // One thing smaller comes after
                after[i] = (*smaller).second;
            } else {
                // More than one thing smaller comes after, so impossible to swap around
                after[i] = -2;
            }
            seen.emplace(-A[i], i);
        }

        int score = 0;
        for (int i = 0; i < N; ++i) {
            if (after[i] == -1 && before[i] == -1 && A[i] == i + 1) score++; // these ones were already correct
        }

        if (score == N) {
            cout << N - 2 << endl;
        } else {
            map<pair<int, int>, int> extra;
            for (int n = 0; n < N; ++n) {
                if (A[n] == n + 1) {// try swapping around it
                    if (before[n] >= 0 && after[n] >= 0) { 
                        assert(before[n] < after[n]);
                        extra[{before[n], after[n]}]++;
                    } 
                } else { // need to put it in the correct place
                         // try swapping index n with index A[n] - 1; only any good if that would be correct
                    if (before[A[n] - 1] == -1 && after[A[n] - 1] == -1) {
                        int l = min(n, A[n] - 1);
                        int r = max(n, A[n] - 1);
                        assert(l != r);
                        extra[{l, r}]++;
                    }
                }
            }

            int best = 0;
            for (auto [pii, sc] : extra) {
                best = max(best, sc);
            }
            cout << best + score << endl;
        }
    }
    return 0;
}