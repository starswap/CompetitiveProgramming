#include <bits/stdc++.h>
#define MULTITEST true
using namespace std;

#define int long long

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

void solve() {
    int n; cin >> n;
    vi nums(n + 2);
    nums[0] = 0;
    nums[n + 1] = 1440;
    rep(i, 0, n) {
        cin >> nums[i+1];
    }
    int m = 0;
    rep(i, 1, n + 2) {
        m += (nums[i] - nums[i-1]) / 120;
    }
    if (m >= 2) {
        cout << "YES" << "\n";
    } else {
        cout << "NO" << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T = 1; if (MULTITEST) cin >> T;
    for (int t = 0; t < T; ++t) solve();
}