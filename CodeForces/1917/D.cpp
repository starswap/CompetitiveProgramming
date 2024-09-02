#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

typedef long long ll;

int solve(const vector<int>& P, const vector<int>& Q, int N, int K) {
    
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N, K; cin >> N >> K;
        vector<int> P;
        vector<int> Q;
        for (int n = 0; n < N; ++n) {
            cin >> P[n];
        }
        for (int k = 0; k < K; ++k) {
            cin >> Q[k];
        }
        cout << solve(P, Q, N, K) << endl;
    }
    return 0;
}