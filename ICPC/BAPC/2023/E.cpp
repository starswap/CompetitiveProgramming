#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int N;
const int MAXN = 2005;
const ll INF = 1'000'000'000'000'000'000;
ll DP[MAXN][MAXN];
int S[MAXN];
int P[MAXN];
int E[MAXN];
int A[MAXN];

int main() {
    cin >> N;
    for (int n = 0; n < N; ++n) {
        cin >> S[n] >> P[n] >> E[n] >> A[n];
    }
    S[N] = 1'000'000'005;
    fill(&DP[0][0], &DP[0][0] + sizeof(DP) / sizeof(DP[0][0]), -INF);

    // DP[i][n] = maximum amount of spare time you have until the start of exam i if you passed n exams before this point.
    DP[0][0] = S[0];
    for (int i = 0; i < N; ++i) {
        for (int n = 0; n <= i + 1; ++n) {
            if (n > 0 && DP[i][n - 1] >= A[i]) {
                DP[i + 1][n] = max(DP[i][n] + S[i + 1] - E[i],
                                   DP[i][n - 1] + S[i + 1] - P[i] - A[i]);
            } else {
                DP[i + 1][n] = (DP[i][n] == -INF) ? -INF : (DP[i][n] + S[i + 1] - E[i]);
            }
        }
    }

    int ans = 0;
    for (int n = 0; n <= N; ++n) {
        if (DP[N][n] > -INF) {
            ans = n;
        }
    }
    cout << ans << endl;

    
    return 0;
}