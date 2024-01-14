#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N, K;
const int MOD = 998244353;

int DP[2503][2503];
void clearDP(int N) {
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= N; ++j) {
            DP[i][j] = -1;
        }
    }
}

int doDP(int a, int last) {
    if (a == 0) {
        return 1;
    } else if (DP[a][last] != -1) {
        return DP[a][last];
    } else {
        int ans = 0;
        for (int next = 1; last * next <= a && last + next - 2 < K; ++next) {
            ans += doDP(a - last * next, next);
            ans %= MOD;
        }
        DP[a][last] = ans;
        return ans;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> K;
        clearDP(N);
        cout << doDP(N, 0) << endl;        
    }
    return 0;
}
