#include <bits/stdc++.h>
using namespace std;

const int MAX_K = 2;
const int MAX_N = 200005;
const int INF = 2 * MAX_N;
int dp[MAX_N][MAX_K];
int N, M, K;
vector<pair<int, int>> intervals;
set<int> dry_cities;
int do_DP(int i, int k) { // position where we are, 
    if (k == 0) return 0;
    else if (dp[i][k] != -1) return dp[i][k];
    else {
        // first interval 

        int thisL = intervals[i].first;
        int nextL = (i == M - 1)  ? intervals[i].second : min(intervals[i].second, intervals[i + 1].first);

        int take_option = do_DP(i + 1, k - 1) + nextL - thisL; // remove this one and go to start of next adding delta
        auto next_it = upper_bound(intervals.begin(), intervals.end(), make_pair(intervals[i].second, INF));
        int leave_option = do_DP(next_it - intervals.begin(), k); // keep this one and go to the end of this one
        dp[i][k] = max(take_option, leave_option);
        return max(take_option, leave_option);
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M >> K;

        intervals.clear();
        dry_cities.clear();
        for (int i = 0; i < N; ++i) {
            dry_cities.insert(i);
        }

        for (int i = 0; i < M; ++i) {
            int l, r; cin >> l >> r;
            l--; r--;
            intervals.emplace_back(l, r);
            set<int> to_remove;
            for (auto start = dry_cities.lower_bound(l); start != dry_cities.upper_bound(r); ++start) {
                to_remove.insert(*start);
            }
            for (int s : to_remove) {dry_cities.erase(s);}
        }
        sort(intervals.begin(), intervals.end());
        for (int i = 0; i < MAX_N; ++i) {
            for (int j = 0; j < MAX_K; ++j) {
                dp[i][j] = -1;
            }
        }

        int baseline_dry_cities = dry_cities.size();
        cout << baseline_dry_cities + do_DP(0, K) << endl; 
    }
    return 0;
}