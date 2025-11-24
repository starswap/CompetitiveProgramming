#include <bits/stdc++.h>


#define int long long
#define MULTITEST true

using namespace std;

vector<int> A;
vector<int> B;
int N, M;

int dp[4005][4005][2];

int doDP(int n, int m, bool b) {
    if (n == N && m == M) {
        return true;
    } else if (n < N && m == M) {
        return b;
    } else if (n >= N) {
        return false;
    } else if (dp[n][m][b] != -1) {
        return dp[n][m][b];
    }  
    else {
        bool ans = false;
        if (A[n] == B[m]) {
            ans = ans || doDP(n + 1, m + 1, 0);
        }
        if (b == 1) {
            ans = ans || doDP(n + 1, m, 1);
        }
        ans = ans || doDP(n + B[m], m + 1, 1);
        dp[n][m][b] = ans;
        return ans;
    }
}

void solve() {
    cin >> N >> M;
    A.resize(N);
    B.resize(M);
    
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    for (int j = 0 ; j < M ;++j) {
        cin >> B[j];
    }

    for (int i = 0; i < N + 2; ++i) {
        for (int j = 0; j < M + 2; ++j) {
            for (int b = 0; b < 2; ++b) {
                dp[i][j][b] = -1;
            }
        }
    }

    cout << (doDP(0, 0, 0) ? "YES" : "NO") << endl;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T = 1; if (MULTITEST) cin >> T;
    while(T--) {
        solve();
    }
}