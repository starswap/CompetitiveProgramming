#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// long long

const int MAX_N = 500000;
const int INF = 1000000010;
const int UNDEF = -INF;
ll DP[MAX_N];
int A[MAX_N];
vector<vector<int>> tree;
int N;
ll ans = 0;

void clear_dp() {
    for (int i = 0; i < N; ++i) {
        DP[i] = UNDEF;
    }
}

ll dp(int u, int p) {
    if (DP[u] == UNDEF) {
        vector<ll> child_scores;
        for (int c : tree[u]) {
            if (c == p) continue;
            child_scores.push_back(dp(c, u));
        }
        sort(child_scores.begin(), child_scores.end());
        reverse(child_scores.begin(), child_scores.end());

        ll total_pos = 0; int num_pos = 0;
        for (ll sc : child_scores)
            if (sc >= 0) {total_pos += sc; num_pos += 1;}
        
        // case where we keep a link to the parent
        DP[u] = max(DP[u], (ll) A[u]);
        if(child_scores.size() >= 1) DP[u] = max(DP[u], child_scores[0]);
        if (child_scores.size() >= 2) DP[u] = max(DP[u], (ll) A[u] + child_scores[0] + child_scores[1]);
        if (num_pos >= 2) {
            DP[u] = max(DP[u], (ll) A[u] + total_pos);
        }

        // case where we don't keep a link to the parent
        ans = max(ans, (ll) A[u]);
        if (child_scores.size() >= 1) ans = max(ans, (ll) A[u] + child_scores[0]);
        if (child_scores.size() >= 2) ans = max(ans, child_scores[0] + child_scores[1]);
        if (child_scores.size() >= 3) ans = max(ans, (ll) A[u] + child_scores[0] + child_scores[1] + child_scores[2]);
        if (num_pos >= 3) {
            ans = max(ans, (ll) A[u] + total_pos);
        }
    }
    return DP[u];
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        tree.assign(N, vector<int>());
        for (int i = 0; i < N - 1; ++i) {
            int u, v; cin >> u >> v;
            u--; v--;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        clear_dp();
        ans = 0;
        dp(0, -1);
        cout << ans << endl;
    }
    return 0;
}