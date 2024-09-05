#include <bits/stdc++.h>
using namespace std;

// Note:
// Constraints for this problem are wrong in the statement:
//  Actual constraints should be:
//      0 <= o <= c < 1000000
//      0 <= w < 100000
//      0 <= d_i < 200000)

const int MAX_N = 100;
const int INF = 1000000007;
const int MAX_T = 1000000; // See note about constraints
const int UNK = -1;
int N, D;

// Including space for dummy
int O[MAX_N + 1];
int C[MAX_N + 1];
int W[MAX_N + 1];
int AM[MAX_N + 1][MAX_N + 1];
int DP[MAX_N + 1][MAX_N + 1];
multimap<int, pair<int, int>> special[MAX_N + 1]; // time, serial -> cafe, special_idx
vector<pair<int, int>> special_v[MAX_N + 1]; // time, cafe

int doDP(int c, int t, int max_t) {
    if (DP[c][t] != UNK) return DP[c][t];
    else {
        const auto &[time, d] = special_v[c][t];
        if (time >= max_t) return (DP[c][t] = 0);
        else if (time == C[c] && d == c) { // closing; have to leave
            DP[c][t] = 0;
            for (int m = 0; m < N; ++m) {
                int arrival_time = max(time + AM[c][m], O[m]);
                if (arrival_time == C[m]) continue;
                auto it = special[m].upper_bound(arrival_time);
                if (it == special[m].end()) continue;
                const auto &[next_time, p] = *it;
                const auto &[_, special_idx] = p;
                int uploaded = max(0, (min(next_time, max_t) - arrival_time)) * W[m];
                DP[c][t] = max(
                    DP[c][t],
                    doDP(m, special_idx, max_t) + uploaded
                );
            }
        } else {
            int uploaded_here = (min(special_v[c][t + 1].first, max_t) - special_v[c][t].first) * W[c];
            DP[c][t] = doDP(c, t + 1, max_t) + uploaded_here;

            auto it = special[d].upper_bound(time + AM[c][d]);
            if (!(it == special[d].end())) { // new one just opened; can we make it?
                const auto &[next_time, p] = *it;
                const auto &[_, special_idx] = p;
                int uploaded = max(0, (min(next_time, max_t) - O[d])) * W[d];
                DP[c][t] = max(
                    doDP(d, special_idx, max_t) + uploaded,
                    DP[c][t]
                );
            }
        } 
        return DP[c][t];
    }
}

int main() {
    cin >> D >> N;
    for (int n = 0; n < N; ++n) {
        cin >> O[n] >> C[n] >> W[n];
    }

    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < N; ++m) {
            cin >> AM[n][m];
        }
    }

    for (int n = 0; n < N; ++n) {
        AM[N][n] = 0;
        AM[n][N] = INF;
    }
    C[N] = INF;

    for (int k = 0; k <= N; ++k)
        for (int i = 0; i <= N; ++i)
            for (int j = 0; j <= N; ++j)
                AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);

    for (int n = 0; n <= N; ++n) {
        special_v[n].emplace_back(C[n], n);
        for (int m = 0; m < N; ++m) {
            int leave_time = O[m] - AM[n][m];
            if (m == n || leave_time >= C[n]) continue;
            special_v[n].emplace_back(leave_time, m);
        }
        sort(special_v[n].begin(), special_v[n].end());
        for (int s = 0; s < special_v[n].size(); ++s) {
            special[n].emplace(special_v[n][s].first, make_pair(special_v[n][s].second, s));
        }
    }
    
    int lo = 0;         // excluded
    int hi = MAX_T + 1; // included

    while (hi - lo > 1) {
        int mi = (hi + lo) / 2;
        fill(&DP[0][0], &DP[0][0] + sizeof(DP)/sizeof(DP[0][0]), UNK) ;
        if (doDP(N, 0, mi) >= D) {// yes we can 
            hi = mi;
        }
        else
            lo = mi;
    }
    if (hi == MAX_T + 1) { // Robin and Jim do this but it's not actually necessary
                           // as no-one checks it in the test cases.
        cout << "impossible" << endl;
    } else {
        cout << hi << endl;
    }

    return 0;
}
