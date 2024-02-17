#include <bits/stdc++.h>
using namespace std;
int MOD = 998244353;

typedef long long ll;

// Returns modulo inverse of a with respect
// to m using extended Euclid Algorithm
// Assumption: a and m are coprimes, i.e.,
// gcd(A, M) = 1
ll modInverse(ll A, ll M)
{
    int m0 = M;
    int y = 0, x = 1;
 
    if (M == 1)
        return 0;
 
    while (A > 1) {
        // q is quotient
        int q = A / M;
        int t = M;
 
        // m is remainder now, process same as
        // Euclid's algo
        M = A % M, A = t;
        t = y;
 
        // Update y and x
        y = x - q * y;
        x = t;
    }
 
    // Make x positive
    if (x < 0)
        x += m0;
 
    return x;
}

ll Choose(ll n, ll k) {
    ll res = 1;
    for (int i = 1; i <= k; ++i) {
        res = (res * (n - k + i)) % MOD;
        res = (res * modInverse(i, MOD)) % MOD;
    }
    return res;
}

void in_order_traversal(vector<int>& res, const vector<pair<int, int>>& children, const vector<int>& values, int i) {
    if (i != -1) {
        in_order_traversal(res, children, values, children[i].first);
        res.push_back(values[i]);
        in_order_traversal(res, children, values, children[i].second);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N, C; cin >> N >> C;
        vector<int> values(N, -1);
        vector<pair<int, int>> children(N);
    
        for (int n = 0; n < N; ++n) {
            int L, R, v;
            cin >> L >> R >> v;
            if (L != -1) L--;
            if (R != -1) R--;
            values[n] = v;
            children[n].first = L;
            children[n].second = R;
        }

        vector<int> res;
        in_order_traversal(res, children, values, 0);

        ll ans = 1;

        int mini = 1;
        int maxi = C;
        int i = 0;
        while (i < N) {
            while (i < N && res[i] != -1) {
                mini = res[i];
                i++;    
            }
            if (i >= N) break;
            int fstI = i;
            while (i < N && res[i] == -1) {
                i++;
            }
            int lstI = i - 1;
            if (i == N) {
                maxi = C;
            } else {
                maxi = res[i];
            }

            ll D = maxi - mini + 1;
            ll L = lstI - fstI + 1;
            ans = (ans * Choose(D - 1 + L, L)) % MOD;
        }
        cout << ans << endl;
    }
    return 0;
}