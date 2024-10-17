#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N; cin >> N;
    vector<int> deltas(N);
    for (int n = 0; n < N; ++n) {
        cin >> deltas[n];
    }

    int lo = -100'000'5;
    int hi = 100'000'5;
    while (hi - lo > 5) {
        int mi1 = lo + (hi - lo) / 3;
        int mi2 = lo + 2 * (hi - lo) / 3;

        ll mi1_ans = 0, mi2_ans = 0;
        for (int i = 0; i < N; ++i) {
            mi1_ans += abs(mi1 + i - deltas[i]);
        }
        for (int i = 0; i < N; ++i) {
            mi2_ans += abs(mi2 + i - deltas[i]);
        }
        if (mi1_ans < mi2_ans) {
            hi = mi2;
        } else if (mi1_ans > mi2_ans) {
            lo = mi1;
        } else {
            lo = mi1;
            hi = mi2;
        }
    }

    
    ll best = 1'000'000'000'000;
    for (int j = lo; j <= hi; ++j) {
        ll ans = 0;
        for (int i = 0; i < N; ++i) {
            ans += abs(j + i - deltas[i]);
        }
        best = min(best, ans);

    }
    cout << best << endl;

    return 0;
}
