#include <bits/stdc++.h>
using namespace std;

// Using the graph method as suggested in the slides.
// This is similar to my original method but different because:
//   - This computes the largest amount that can be uploaded by a given time/node combo rather than largest amount by the end time
//   - The DP is computed bottom up
//   - You get away with the cycle problem when it takes 0 seconds to go between sites because there's never a case when you want to travel between two sites at opening or closing if we assume that the AM has no weirdness where it makes sense to go via somewhere instead of direct. This is the case for the provided data but could be ensured anyway by APSP if necessary.
// Nicer because:
//    - No need for BSTA since the time is calculated "as we go" on the basis of "upload the most by this time/location pair" must yield the quickest time when all times and locations considered.
//    - Avoids annoyances due to cycle problem, and need for all the set iterator stuff, by treating moving separately from staying somewhere and not needing to worry about 0 length moves.
// Note:
// Constraints for this problem are wrong in the statement:
//  Actual constraints should be:
//      0 <= o <= c < 1000000
//      0 <= w < 100000
//      0 <= d_i < 200000

const int MAX_N = 100;
const int INF = 1000000007;
const int MAX_T = 1000000; // See note about constraints
int N, D;

map<pair<int, int>, vector<pair<int, int>>> AL; // time, cafe 
map<pair<int, int>, vector<pair<int, int>>> AL_rev; // time, cafe 
map<pair<int, int>, int> scores;
set<int> cafe_to_time[MAX_N];

int O[MAX_N];
int C[MAX_N];
int W[MAX_N];
int AM[MAX_N][MAX_N];

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
        for (int m = 0; m < N; ++m) {
            if (m == n) continue;
            AL[make_pair(C[n], n)].push_back(make_pair(C[n] + AM[n][m], m));
            int leave_time = O[m] - AM[n][m];
            AL[make_pair(leave_time, n)].push_back(make_pair(O[m], m));
            cafe_to_time[n].insert(C[n]);
            cafe_to_time[n].insert(leave_time);
            cafe_to_time[m].insert(O[m]);
            cafe_to_time[m].insert(C[n] + AM[n][m]);
        }
    }
    
    for (int n = 0; n < N; ++n) {
        for (auto it = cafe_to_time[n].begin(); it != prev(cafe_to_time[n].end()); ++it) {
            AL[make_pair(*it, n)].emplace_back(*next(it), n);
        }
    }

    for (const auto& [p, v] : AL) {
        for (const auto& p2 : v) {
            AL_rev[p2].push_back(p);
        }
    }

    scores[AL.begin()->first] = 0;

    int ans = INF;
    for (const auto& [p, v] : AL_rev) {
        for (auto p2 : v) {
            int end_time = min(p.first, C[p.second]);
            int start_time = max(p2.first, O[p.second]);
            int delta = (p.second == p2.second ? (W[p.second] * max(0, (end_time - start_time))) : 0);
            scores[p] = max(scores[p], scores[p2] + delta);
            if (scores[p2] + delta >= D && scores[p2] < D) {
                int this_ans = start_time + ceil(((double) (D - scores[p2])) / ((double) W[p.second]));
                ans = min(ans, this_ans);
            }
        }
    }

    cout << ans << endl;
    return 0;
}
