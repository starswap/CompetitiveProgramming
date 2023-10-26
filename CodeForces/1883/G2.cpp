#include <bits/stdc++.h>
using namespace std;

int N, M;

int solve(vector<int> a, vector<int> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int shifts = 0;
    for (int n = 0; n < N; ++n) {
        int thisShift = upper_bound(b.begin(), b.end(), a[n]) - b.begin() - n; // i thi right?
        shifts = max(shifts, thisShift);
    }
    return shifts;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M;
        vector<int> a(N);
        vector<int> b(N);
        a[0] = 0;
        for (int n = 1; n < N; ++n) {
            cin >> a[n];
        }
        for (int n = 0; n < N; ++n) {
            cin >> b[n];
        }

        int lo = 0; // equals the last one with 0
        int hi = M + 1; // equals the first one with 1
        int score0 = solve(a, b); 
        while (hi - lo > 1) {
            int mi = (hi + lo) / 2;
            a[0] = mi;
            int scoreNow = solve(a, b);
            if (scoreNow - score0 == 1) {
                hi = mi; 
            } else {
                lo = mi;
            }
        }
        long long ans = (long long) score0 * lo + ((long long) score0 + 1) * (M - lo);
        cout << ans << endl;
    }
   return 0;
}
