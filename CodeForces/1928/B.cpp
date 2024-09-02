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
        sort(A.begin(), A.end());
        map<int, int> window_cnts;
        int lp = 0; // next element to bin
        int rp = 0; // next element to add
        int score = 0;
        while (lp < (int) A.size()) {
            if (rp < A.size() && (window_cnts.size() == 0 || A[rp] - window_cnts.begin()->first < N)) {
                window_cnts[A[rp]] += 1;
                rp++;
            } else {
                window_cnts[A[lp]] -= 1;
                if (window_cnts[A[lp]] == 0) {
                    window_cnts.erase(A[lp]);
                }
                lp++;
            }
            score = max(score, (int) window_cnts.size());
        }
        cout << score << endl;
    }
    return 0;
}