#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_N = 10000;
ll dp[MAX_N + 5];
const ll INF = 1'000'000'000'000'000'000;

int main() {
    int N, K; cin >> N >> K;
    vector<int> day_i(N);
    vector<int> fares(N);

    vector<int> fare_sums(N);

    vector<vector<int>> passes(K, vector<int>(3)); 
   
    for (int n = 0; n < N; ++n) {
        cin >> day_i[n] >> fares[n];
    }
    
    int tot = 0;
    for (int i = 0; i < N; ++i) {
        tot += fares[i];
        fare_sums[i] = tot;
    }

    for (int k = 0; k < K; ++k) {
        for (int i = 0; i < 3; ++i) {
            cin >> passes[k][i];
        }
    }

    dp[N] = 0;
    for (int t = N - 1; t >= 0; --t) {
        dp[t] = INF;
        dp[t] = min(dp[t], dp[t + 1] + (ll) fares[t]);
        for (int i = 0; i < K; ++i) {
            // TAKE THE ITH PASS
        
            int period = passes[i][0];
            int travel_days = passes[i][1];
            ll cost = passes[i][2];

            int lo = t;
            int hi = N;

            int last_day = day_i[t] + period - 1; 

            while (hi - lo > 1) {
                int mi = (lo + hi) / 2;
                if (day_i[mi] > last_day) {
                    hi = mi;
                } else {
                    lo = mi;
                }
            }

            int first_paying_day = 1 + min(lo, t + travel_days - 1);
            
            dp[t] = min(dp[t], dp[first_paying_day] + cost); 
        }
    }
    cout << dp[0] << endl;

    return 0;
}
