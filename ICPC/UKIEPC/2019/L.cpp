#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
const int MAX_R = 14;
const int MAX_T = 1 << MAX_R;
long long dpNA[MAX_T];
long long dpNB[MAX_T];
long long skill[MAX_T];
long long* dpCurr;
long long* dpPrev;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;
    int T = 1 << N;
    for (int n = 0 ; n < T; ++n) {
        cin >> skill[n];
    }

    for (int r = 0; r < N; ++r) {
        dpCurr = (r % 2 == 0) ? dpNA : dpNB;
        dpPrev = (r % 2 == 0) ? dpNB : dpNA;

        for (int t = 0; t < T; ++t) {
            // 1 << (r + 1) // should be the same as t in both
            // 1 << (r) // should be opposite to t in both
            
            int oppMin = (t & ~((1 << (r + 1)) - 1)) | (~(t & (1 << r)) & (1 << r));
            int oppMax = oppMin | ((1 << r) - 1);
            dpCurr[t] = INF;
            for (int opp = oppMin; opp <= oppMax; ++opp) { 
                dpCurr[t] = min(dpCurr[t], dpPrev[t] + ((skill[t] < skill[opp]) ? (skill[t] - skill[opp])*(skill[t] - skill[opp]) : 0) + dpPrev[opp]);
            }
            
        }
    }
    // cout << skill[1] * skill[1] << endl;
    cout << dpCurr[0] << endl;

    return 0;
}