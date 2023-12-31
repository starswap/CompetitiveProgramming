#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const int MAX_N = 300000;
const int UNDEFINED = -1;

ll res[MAX_N + 5]; 
ll dp[MAX_N + 5];
ll dp_S[MAX_N + 5];
int L[MAX_N + 5];
int A[MAX_N];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        for (int n = 0; n < N; ++n) {
            cin >> A[n];
        }

        stack<int> monotonic;
        for (int i = 0; i < N; ++i) {
            while (!monotonic.empty() && A[monotonic.top()] > A[i]) {
                monotonic.pop();
            }
            L[i] = (monotonic.empty()) ? UNDEFINED : monotonic.top();
            monotonic.push(i); 
        }

        dp[0] = 1;
        dp_S[0] = dp[0];
        res[0] = dp[0];
        for (int n = 1; n < N; ++n) {
            if (L[n] == UNDEFINED) {
                dp[n] = (dp_S[n - 1] + 1) % MOD;
                res[n] = dp[n];
            } else {
                dp[n] = (res[L[n]] + (dp_S[n - 1] - dp_S[L[n]]) % MOD) % MOD; 
                res[n] = (res[L[n]] + dp[n]) % MOD;
            }
            dp_S[n] = (dp_S[n - 1] + dp[n]) % MOD;
        }

        cout << (res[N - 1] + MOD) % MOD << endl;

    }
    return 0;
}