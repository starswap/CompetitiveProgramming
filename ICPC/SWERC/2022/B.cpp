#include <bits/stdc++.h>
#define MULTITEST false
using namespace std;

// #define int long long

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

double dp[105][105];
int R[15];
double P[15];

inline double plt(int e, int k) {
    return dp[e][k];
}

inline double peq(int e, int k) {
    return (k == 0) ? dp[e][k] : dp[e][k] - dp[e][k - 1];
}

inline double pgt(int e, int k) {
    return (1 - (k == 0 ? 0 : dp[e][k - 1]));
}

void solve() {
    int N, M; cin >> N >> M;

    for (int m = 0; m < M; ++m) {
        cin >> R[m];
    }

    for (int k = 0; k <= 100; ++k) {
        dp[N][k] = 1;
    }

    for (int k = 0; k <= 100; ++k) {
        for (int e = N - 1; e >= 1; e--) {
            double u = (1.0/static_cast<double>(N - e));
            for (int j = e + 1; j <= N; ++j) {
                dp[e][k] += (k - 1 >= 0) ? (u * dp[j][k - 1]) : 0.0;
            }
        }
    }


    for (int i = 0; i < M; ++i) {
        for (int k = 0; k <= 100; ++k) {
            double this_p = peq(R[i], k);
            for (int j = 0; j < M; ++j) {
                if (i == j) continue;
                // if (dp[R[i]][k] * pgt(R[j], k) > 0) {
                    // cout << i << " " << k << " " << j << " " << dp[R[i]][k] * pgt(R[j], k) << endl;
                // }
                this_p *= pgt(R[j], k);
            }
            P[i] += this_p;
        }
    }

    for (int i = 0; i < M; ++i) {
        cout << P[i] << " ";
    }

    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout << fixed << setprecision(10); 
    int T = 1; if (MULTITEST) cin >> T;
    for (int t = 0; t < T; ++t) solve();
}
